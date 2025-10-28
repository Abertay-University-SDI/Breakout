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
<Add information to this section about the time you've taken for this task along with a professional changelist.>

- Bug Fix 'PowerupFireball.h' (5 minutes)
- Added multi hit functionality to the bricks to make fireball more impactful (1 hr)
- Removed fireball's ability to pass through objects, fireball now destroys undamaged blocks (30 minutes)
- Added infectionball (1.45 hr)
- Infectionball now damages surrounding objects correctly (30 minutes)
- Fixed issue with infectionball lingering after duration faded, changed colouring and reworked collisions (1 hr)
- Made function to help damage bricks (15 minutes)
