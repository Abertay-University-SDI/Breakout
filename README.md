# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

You are to spend between three and eight hours improving this simple Breakout implementation in a way to best demonstrate your capabilities as a games programmer. 

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* Add an actual game loop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball, brick-tracking ball)
    * Note: smallPaddle is too simple to be impressive.
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as Ollama

# Time Details and Changelist

Total time: approximately 4 hours.

### Hour 1 – Ray marched 3D rendering
Reused my previous approach of ray marching in a fragment shader to make the game 3D, with gameplay and collision logic left unchanged.
* Added `shaders/raymarch.frag`, which draws the whole scene in one fullscreen pass using signed distance fields: rounded boxes for bricks and the paddle, spheres for the ball and powerups.
* Added a `Raymarch` module that collects each frame's shapes and passes their position, size and colour to the shader as uniform arrays. Each object's `render()` now registers its shape (`Raymarch::add`) instead of drawing it directly.
* A perspective camera is aimed so the gameplay plane maps 1:1 onto screen pixels, so shapes line up exactly with their collision bounds.
* Lighting: diffuse and specular shading, soft shadows cast onto a back wall, ambient occlusion, rim lighting and a vignette.
* Optimisations: rays skip the empty space in front of the scene, and normals use the 4-sample tetrahedral method.

### Hour 2 – Hit feedback: screen shake and liquid particles
* Screen shake a strong shake on losing a life and a light shake on breaking a brick. It fades out over its duration, and a weaker shake never interrupts a stronger one.
* New `Particles` system: breaking a brick bursts it into liquid drops in the brick's colour. Drops have gravity, drag, cohesion and separation forces, bounce off the walls, and land on and slide off the paddle.
* In the shader, drops are blended with a polynomial smooth min so nearby drops merge into one liquid surface and melt into the bricks and paddle they touch. Where drops meet, their colours mix, and the liquid has its own glossier material.
* A bounding-box early-out skips the per-particle work for rays far from any liquid.

### Hour 3 – Gameplay loop
* Added a `GameState` state machine (Serving, Playing, LevelComplete, GameOver) in place of the game freezing on game over or level complete.
* Serving: the ball rests on the paddle until SPACE launches it, at the start of each level and after each lost life.
* Scoring: each brick is worth 10 points × the current level. The score and level are shown in the UI.
* Level progression: clearing all bricks leads to the next level, with an extra brick row (up to 6) and a 10% faster ball. Powerups, active effects and the paddle size are reset between levels.
* Game over shows the final score, and SPACE starts a new game with lives, score and level reset.
* Centred on-screen prompts for each state, including pause.

### Hour 4 – Polish
* The paddle now also produces a splash when it hits the ball, in the ball's colour (including fireball orange).
* Splashes launch upward in a wide fan (±70°) at higher speed before falling, for a more energetic impact.
* Tuned liquid cohesion, separation and blend size so splashes read as liquid without clumping into one point.
* Fixed shader artefacts: clipped blobs where merged drops swelled past the front of the scene, and visible seams at the edges of the liquid bounding box.
* Made the ball larger (radius 10 → 15) and changed its colour to hot pink so it stands out from the cyan paddle.

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!