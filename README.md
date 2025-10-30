# Breakout

W Kavanagh & N Merchant. Summer 2024 

## controls

A/D to move the paddle right and left.
<br/>
P to pause.

### Added
Left Mouse and drag to move the paddle left and right

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code - Fixed

## Suggested tasks

* Implement mouse input for pad - Implemented
* Improved VFX (ball trail, paddle hit response, brick particle destruction) - Implemented
* Better UI (progress bar rather than timer for countdown). - Implemented
* GameLoop - Implemented
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
<Add information to this section about the time you've taken for this task along with a professional changelist.>
- Removed #include "PowerupFireBall.h" In PowerupBase.h as this creates a circular dependancy. PowerupFireball is already dependenet on PowerupBase
- Added Moving the paddle based on the poition of the mouse relative to the paddle. This only applies if left mouse is clicked and is based on the centre of the paddle.
- Added a trail to the ball and power ups. Power up trail is the same as the power up color, ball trail is white.
- Added Screen shake added when the ball hits the paddle, bricks and walls.
- Added progress bar instead of timer for power ups
- Added particle effects for when the bricks break
- Added ability to restart the game
