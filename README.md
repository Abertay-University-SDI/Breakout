# Breakout

W Kavanagh \& N Merchant. Summer 2024

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
* More ball types (e.g., multiball, sticky ball \[where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist

* Fixed compiler issues in the code - 10 minutes
* Added basic gameloop, game resets when level is completed or game over, with a delay where the game is paused in-between - 1 hour
* The ball now waits a delay and blinks before moving when respawning - 1 hour
* Added bomb ball powerup, which destroys bricks surrounding the initial brick hit by the ball - 1 hour
