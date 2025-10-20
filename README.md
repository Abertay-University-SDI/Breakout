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

* Fix the compiler issues in the code - Done!

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


Ari Alexander Tannahill Thomson - 2204636


Change 1 - fixed the compiler issue. Removed the circular reference from PowerupBase (10 minutes)

Change 2 - added multiple health to bricks, the bricks have a different colour based on their health, this colour changes as they are hit (1 hour)

Change 3 - added sfx on brick being destroyed (30 minutes)

Change 4 - added a "gun" to the cursor that the player can shoot at the bricks every 3 seconds to damage them, it plays a sound effect also (1 hour)

Change 5 - parameterised the powerup spawn chance (5 minutes)

Change 6 - added screen shake on damage taken (45 mins)



Total time spent - 3 hours 35 minutes

