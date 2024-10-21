# Breakout

W Kavanagh. June Summer 2024

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist

Patch Notes:
- Adjusted ball physics to account for the paddles movement direction
- Added gravity to the ball
- Added particle effects to blocks on destroy
- Fixed bug

Timings:
- Fixed Bug (15 mins)
- Adjusted Ball Physics (30 mins)
- Refined Ball Physics (45 mins)
- Fix Gravity (30 mins)
- Added Particles (30 mins)
- Refactored Particle Code (1 hour)
- Added Particle Effect Logic (1 hour)
- Added Lerp to Particles (30 mins)
