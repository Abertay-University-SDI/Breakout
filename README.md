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
* Fixed compiler issue - Time Taken: 3 minutes
* Added mouse movement for the paddle and hidden & locked cursor - Time taken: 1 hour 
* Created a restart function upon level loss or completion - Time taken: 15 minutes
* Added a screen shake whenever the player loses a life - Time taken: 45 minutes
* Added a trail following the ball's position - Time taken: 30 minutes
* Created an audio manager to handle sound effects and background music - Time taken: 1 hour 15 minutes
* Changed the power up timer to a decreasing bar instead of text - Time taken: 10 minutes
