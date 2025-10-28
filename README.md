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

Robert Bryson

Fixed compiler error - Circular dependency caused by include "PowerupFireBall.h" in "PowerupBase.h", removed include as was unused - \*3 minute

Added mouse controls - New function "followMouse()" in Paddle. Player is given choice, which is stored as bool and passed to game manager, in update calls appropriate control scheme - \*25 minutes

Parameterised powerUpChance - added variable used for rand() that decides when power up spawns - \*2 minutes

Screen Shake - First tried shaking the whole window, moving the window itself, however this felt bad and wouldn't work on a full screen version of the game, so changed to shaking everything within the window. On lost life sets shake bool to true, this is checked in update along with other parameters such as intervals, and length, to shake the components of the scene - \*45 minutes

Power up fix - Not entirely sure what was expected but have converted the case 5 to default, as rand()%5 can only be 0 - 4, this also protects against any issues with corruption - \*5 minutes

Secondary ball powerup - Removed ball and powerup includes from GameManager.h to instead use forward declaration, this will allow the powerup to spawn a new ball in the game manager. Added new vector (\_secondaryBalls) to game manager to track these balls, these are created and deleted accurately and safely. Added bool to ball constructor to set as primary, this allows secondary balls to look different, and not effect health or be effected by powerups. This powerup displays as green, "extraBallEffectsColour" - \*90 minutes

Further testing - Tested how well these features work extensively. Found and fixed wrong text in control input, wrong colour on secondary balls - \*25 minutes

