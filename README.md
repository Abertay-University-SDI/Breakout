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
> v1.5 [15 minutes]
> - Added some Math functions for Vector2f manipulation
> - Bricks now get nudged when hit by the ball

> v1.4 [10 minutes]
> - Brick Health and changing color based on health
> - Drawing score on win/lose, until leadeboard is received

> v1.3 [50 minutes]
> - Drawing leaderboard on client
> - Moving the server code from main to ServerApplication class
> - Debugging UdpSocket not receiving data

> v1.2 [60 minutes]
> - Server Application Prototype
> - Started Client-side network implementation
 
> v1.1 [55 minutes]
> - Leaderboard research

> v1.0 [5 mins]
> - Fixed compilation issue