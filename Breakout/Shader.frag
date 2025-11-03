uniform sampler2D texture;
uniform float time;
uniform vec2 resolution;
uniform sampler2D lightTex;

void main()
{
	vec2 uv = gl_FragCoord.xy / resolution;
	vec4 col = texture2D(texture, uv);

	//col.r += sin(time * 10);
	col *= texture2D(lightTex, uv) * 2;

	gl_FragColor = vec4(col.rgb, 1.0);
}