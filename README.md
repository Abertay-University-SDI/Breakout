# Breakout

W Kavanagh & N Merchant. Summer 2024 

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

Fast Ball - Yellow
Slow Ball - Blue
Big paddle - Purple
Small Paddle - Green
Fast Paddle - Cyan
Slow Paddle - Pink
Fireball - Red
Big Ball - Magenta
Small Ball - White
Sticky Ball - Dark yellow (gluelike)
Godmode - Brown

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code - Done

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
10 min - Fixed circular dependency

3 1/2 hrs - Refactored and overhauled powerup system, remanaged object responsibilities
New powerups rely on composition rather then pure inheritence, makes it easier to reuse common effects like speed or size

30 minutes - Added new powerups
Paddle speed - Increase or decrease the speed of the paddle
Sticky ball - Ball sticks to the paddle, press space to launch it
Godmode - Ball acts as fireball + cannot lose lives

