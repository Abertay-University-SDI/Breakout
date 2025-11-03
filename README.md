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

<Add information to this section about the time you've taken for this task along with a professional changelist.>



Time Details

* Fixed compiler error: 10mins
* Added Mouse control for paddle: 40mins
* Added Progress bar for powerups: 1hr 15mins
* Total time: 2hrs 5mins



Changelist

* Fixed Compiler error by removing PowerupFireBall.h from PowerupBase header file
* Added Mouse control for paddle using sf::Mouse::getPosition(\*\_window) then realised can just use sf::Mouse::getPosition(\*\_window).x
* Added Progress bar for powerups by creating a rectangle for the background and a fill rectangle that scales with the time remaining of the powerup



