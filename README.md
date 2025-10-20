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

* Implement mouse input for pad \[x]
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball \[where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist

~0:02 - fix circular dependency compiler error

~0:30 - add mouse control for paddle

~1:10 - begin to add powerup that extends the timer for future powerups. right now only ui timer properly updates

~2:00 - add screenshake on life loss

~2:05 - remove strange memory leak in PowerupFireBall.cpp

~2:45 - add ability to reset game on death/win

~2:47 - improve powerup spawn time logic

~3:10 - fix timer extension powerup, now powerups actually get the time extension

~3:15 - actually parameterize powerup spawn