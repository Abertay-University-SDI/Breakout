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
Time taken: 04:43:27.04

Work Done
- Fixed implicated conversion(float, doable) warning in PowerupBase.cpp.
- Implemented a screen shake effect on lose of life.
- Implemented a progress bar for the powerup duration replacing the countdown.
- Implemented mouse-based paddle movement.
- Implemented toggling of the mouse-based paddle movement through the 'M' key.
- Added a "handleInput()" to the GameManager class.
- Implemented a SoundManager for playing audio clips.
- Turned the SoundManager into a singleton.
- Added sounds effects into the game, different ball hit sounds depending on if it's hitting the bricks or something else, a hurt sound for when the player looses a life, and a sound for when a level is completed.