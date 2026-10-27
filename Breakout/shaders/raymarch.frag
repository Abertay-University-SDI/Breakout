#version 120

uniform vec2 iResolution;  // window size in pixels (gl_FragCoord space)
uniform vec2 ViewSize;     // SFML view size, the space the game logic works in
uniform vec2 ViewOrigin;   // top-left of the SFML view; moves when the screen shakes

// Shapes registered by the game each frame, in SFML pixel coordinates (y down).
// MAX_BOXES / MAX_SPHERES / MAX_PARTICLES must match Raymarch.cpp.
#define MAX_BOXES 64
#define MAX_SPHERES 16
#define MAX_PARTICLES 48
uniform vec4 Boxes[MAX_BOXES];          // (left, top, width, height)
uniform vec3 BoxColours[MAX_BOXES];
uniform int BoxCount;
uniform vec3 Spheres[MAX_SPHERES];      // (centre x, centre y, radius)
uniform vec3 SphereColours[MAX_SPHERES];
uniform int SphereCount;
uniform vec3 Particles[MAX_PARTICLES];  // (centre x, centre y, radius)
uniform vec3 ParticleColours[MAX_PARTICLES];
uniform int ParticleCount;
uniform vec4 ParticleBounds;            // (left, top, right, bottom) around every particle

// World space is SFML pixel space: x right, y down, z towards the camera.
// Everything sits on the z = 0 plane, so shapes line up exactly with the game's collision boxes.
const float CAMERA_DISTANCE = 2000.0;
const float WALL_DEPTH      = 40.0;   // back wall the shadows fall on
const float FRONT_Z         = 30.0;   // nothing is closer to the camera than this
const float BOX_ROUNDING    = 4.0;

// Liquid: particles melt into each other with LIQUID_K, and into solid shapes with SOLID_K.
// Every smooth min swells the surface a little, so a clump of drops grows by up to LIQUID_SWELL.
const float LIQUID_K            = 16.0;
const float SOLID_K             = 8.0;
const float MAX_PARTICLE_RADIUS = 10.0;
const float LIQUID_SWELL        = 12.0;
// Beyond this distance the liquid's bounding box stands in for it. It's far enough that
// shadows and ambient occlusion can't tell the difference, so no seams show at the box edges.
const float LIQUID_BOUND_MARGIN = 24.0;

const int   MAX_STEPS       = 80;
const int   SHADOW_STEPS    = 32;
const float HIT_EPSILON     = 0.05;

const float MAT_WALL   = 0.0;
const float MAT_BOX    = 1.0;   // + box index
const float MAT_SPHERE = 100.0; // + sphere index
const float MAT_LIQUID = 200.0;

const vec3 WALL_COLOUR_A = vec3(0.06, 0.07, 0.12);
const vec3 WALL_COLOUR_B = vec3(0.09, 0.10, 0.17);
const float WALL_TILE    = 40.0;

const vec3  LIGHT_DIR = normalize(vec3(-0.5, -0.8, 1.0)); // up-left and in front (y is down)
const float AMBIENT   = 0.25;

// ---------------------------------------------------------------- primitives

float sphereSDF(vec3 p, float r)
{
	return length(p) - r;
}

float boxSDF(vec3 p, vec3 b)
{
	vec3 d = abs(p) - b;
	return min(max(d.x, max(d.y, d.z)), 0.0) + length(max(d, 0.0));
}

float roundBoxSDF(vec3 p, vec3 b, float r)
{
	return boxSDF(p, b - r) - r;
}

// (distance, material) pairs
vec2 opUnion(vec2 a, vec2 b)
{
	return (a.x < b.x) ? a : b;
}

// Polynomial smooth min: blends the two surfaces together within k of each other.
float smoothMin(float a, float b, float k)
{
	float h = max(k - abs(a - b), 0.0) / k;
	return min(a, b) - h * h * k * 0.25;
}

// ---------------------------------------------------------------- scene

// A rectangle becomes a rounded bar as deep as it is tall.
float boxShapeSDF(vec3 p, vec4 rect)
{
	vec2 halfSize = rect.zw * 0.5;
	vec3 centre = vec3(rect.xy + halfSize, 0.0);
	float r = min(BOX_ROUNDING, min(halfSize.x, halfSize.y));
	return roundBoxSDF(p - centre, vec3(halfSize, halfSize.y), r);
}

float liquidSDF(vec3 p)
{
	float d = 1e10;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (i >= ParticleCount) break;
		d = smoothMin(d, sphereSDF(p - vec3(Particles[i].xy, 0.0), Particles[i].z), LIQUID_K);
	}
	return d;
}

// Lower bound on the distance to the liquid, so rays away from it skip the particle loop.
float liquidBound(vec3 p)
{
	vec2 halfSize = (ParticleBounds.zw - ParticleBounds.xy) * 0.5;
	vec3 centre = vec3(ParticleBounds.xy + halfSize, 0.0);
	return boxSDF(p - centre, vec3(halfSize, MAX_PARTICLE_RADIUS)) - LIQUID_SWELL;
}

vec2 map(vec3 p)
{
	vec2 res = vec2(1e10, MAT_BOX);

	for (int i = 0; i < MAX_BOXES; i++)
	{
		if (i >= BoxCount) break;
		res = opUnion(res, vec2(boxShapeSDF(p, Boxes[i]), MAT_BOX + float(i)));
	}
	for (int i = 0; i < MAX_SPHERES; i++)
	{
		if (i >= SphereCount) break;
		res = opUnion(res, vec2(sphereSDF(p - vec3(Spheres[i].xy, 0.0), Spheres[i].z), MAT_SPHERE + float(i)));
	}

	if (ParticleCount > 0)
	{
		float bound = liquidBound(p);
		if (bound > LIQUID_BOUND_MARGIN)
			res = opUnion(res, vec2(bound, MAT_LIQUID));
		else
		{
			// Liquid melts into whatever solid it touches.
			float liquid = liquidSDF(p);
			res = vec2(smoothMin(res.x, liquid, SOLID_K), liquid < res.x ? MAT_LIQUID : res.y);
		}
	}

	return opUnion(res, vec2(p.z + WALL_DEPTH, MAT_WALL));
}

// Tetrahedron technique: 4 map calls instead of 6.
vec3 getNormal(vec3 p)
{
	const vec2 k = vec2(1.0, -1.0);
	const float e = 0.01;
	return normalize(
		k.xyy * map(p + k.xyy * e).x +
		k.yyx * map(p + k.yyx * e).x +
		k.yxy * map(p + k.yxy * e).x +
		k.xxx * map(p + k.xxx * e).x);
}

bool march(vec3 ro, vec3 rd, out vec3 p, out float material)
{
	// Skip the empty space between the camera and the scene in one step.
	float t = (ro.z - FRONT_Z) / -rd.z;
	material = MAT_WALL;
	for (int i = 0; i < MAX_STEPS; i++)
	{
		p = ro + t * rd;
		vec2 res = map(p);
		if (res.x < HIT_EPSILON)
		{
			material = res.y;
			return true;
		}
		t += res.x;
	}
	return false;
}

float softShadow(vec3 ro, vec3 rd)
{
	float res = 1.0;
	float t = 0.5;
	for (int i = 0; i < SHADOW_STEPS; i++)
	{
		vec3 p = ro + rd * t;
		if (p.z > FRONT_Z) break; // left the scene towards the light
		float h = map(p).x;
		if (h < HIT_EPSILON)
			return 0.0;
		res = min(res, 8.0 * h / t);
		t += clamp(h, 0.5, 20.0);
	}
	return clamp(res, 0.0, 1.0);
}

float ambientOcclusion(vec3 p, vec3 n)
{
	float occ = 0.0;
	float weight = 1.0;
	for (int i = 1; i <= 4; i++)
	{
		float h = 4.0 * float(i);
		occ += (h - map(p + n * h).x) * weight;
		weight *= 0.6;
	}
	return clamp(1.0 - occ * 0.04, 0.0, 1.0);
}

// ---------------------------------------------------------------- shading

// Where drops have merged their colours mix, weighted by how close each drop is.
vec3 liquidColour(vec3 p)
{
	vec3 sum = vec3(0.0);
	float total = 0.0;
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (i >= ParticleCount) break;
		float d = max(sphereSDF(p - vec3(Particles[i].xy, 0.0), Particles[i].z), 0.0);
		float w = 1.0 / (1.0 + d * d * 0.05);
		sum += ParticleColours[i] * w * w;
		total += w * w;
	}
	return sum / max(total, 1e-4);
}

// GLSL 1.20 only guarantees uniform array indexing with loop counters.
vec3 materialColour(float material, vec3 p)
{
	if (material == MAT_LIQUID)
		return liquidColour(p);
	if (material >= MAT_SPHERE - 0.5)
	{
		int index = int(material - MAT_SPHERE + 0.5);
		for (int i = 0; i < MAX_SPHERES; i++)
			if (i == index) return SphereColours[i];
	}
	else if (material >= MAT_BOX - 0.5)
	{
		int index = int(material - MAT_BOX + 0.5);
		for (int i = 0; i < MAX_BOXES; i++)
			if (i == index) return BoxColours[i];
	}

	// Back wall: subtle checkerboard.
	float checker = mod(floor(p.x / WALL_TILE) + floor(p.y / WALL_TILE), 2.0);
	return mix(WALL_COLOUR_A, WALL_COLOUR_B, checker);
}

vec3 shade(vec3 p, vec3 rd, vec3 normal, float material)
{
	vec3 colour = materialColour(material, p);

	float diffuse = max(dot(normal, LIGHT_DIR), 0.0);
	float shadow = diffuse > 0.0 ? softShadow(p + normal * 0.1, LIGHT_DIR) : 0.0;
	float ao = ambientOcclusion(p, normal);

	vec3 lit = colour * (AMBIENT * ao + diffuse * shadow * (1.0 - AMBIENT));

	if (material != MAT_WALL)
	{
		// Liquid is glossier, with a tighter, brighter highlight.
		bool liquid = material == MAT_LIQUID;
		vec3 halfVec = normalize(LIGHT_DIR - rd);
		float specular = pow(max(dot(normal, halfVec), 0.0), liquid ? 120.0 : 48.0) * shadow;
		float rim = pow(1.0 - max(dot(normal, -rd), 0.0), 3.0);
		lit += vec3(specular * (liquid ? 1.2 : 0.6)) + colour * rim * (liquid ? 0.7 : 0.4);
	}
	return lit;
}

// ---------------------------------------------------------------- main

void main()
{
	// gl_FragCoord is in window pixels with y up; the game works in view pixels with y down.
	vec2 screen = vec2(gl_FragCoord.x, iResolution.y - gl_FragCoord.y) * ViewSize / iResolution;
	vec2 pixel = ViewOrigin + screen;

	// Perspective camera aimed so the z = 0 plane maps 1:1 onto the game's pixels.
	vec3 ro = vec3(ViewOrigin + ViewSize * 0.5, CAMERA_DISTANCE);
	vec3 rd = normalize(vec3(pixel, 0.0) - ro);

	vec3 p;
	float material;
	vec3 colour = WALL_COLOUR_A;
	if (march(ro, rd, p, material))
		colour = shade(p, rd, getNormal(p), material);

	// Gentle vignette.
	vec2 uv = screen / ViewSize - 0.5;
	colour *= 1.0 - 0.35 * dot(uv, uv);

	gl_FragColor = vec4(pow(colour, vec3(1.0 / 1.2)), 1.0);
}
