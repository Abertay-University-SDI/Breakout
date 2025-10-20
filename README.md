# Breakout

W Kavanagh & N Merchant. Summer 2024 

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
Fixed Compiler error where project would not build. due to a Circular dependency.  - 10 Minutes
Added a ping effect when the ball hits a birck. the pitch for this sound is increased with every hit and reset when the ball hits the padel - 1 Hour

Removed includes int Ball.h and replaced them with forward declearations to avoid Circular dependency and Added a view object - 20 Minutes
Created an effect where when a ball hits a brick the screen shakes slightly. - 30 Minutes
Created an effect where when a ball hits the players, the paddle will flicker - 30 Minutes

