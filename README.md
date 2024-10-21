# Breakout

W Kavanagh. June Summer 2024

# Further fixes and improvements
S Thomas. 2101106

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

---------------* Fix the compiler issues in the code -----------

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
<Add information to this section about the time you've taken for this task along with a professional changelist.>

* Fixed the compiler issues with the PowerupBase.h, by not calling PowerupFireball.h in PowerupBase.h. This took about twenty minutes of googling and digging around in the output.
* Made the pausing more robust by adding a state machine to keep track of the game. Separated the input handling and pausing logic for easier modification in the future. Also added debounce logic to prevent rapid state changes. This took about an hour with research.
* Added screen shaking after the player loses a life. ~thirty minutes
* Added a game loop and reset to the game manager. ~ hour
