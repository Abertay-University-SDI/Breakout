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
<Add information to this section about the time you've taken for this task along with a professional changelist.>

(~15 mins)
Compiler issue fixed. Issue was a circular dependancy in the powerup baseclass where it had a reference to the
Fireball class which uses powerup baseclass as its parent. issue was fixed by removing the unnecessary include.

(~1 hour)
Added mouse controls to the paddle so can now be controlled with either the mouse or the keyboard, if the mouse is over the
window mouse controls are prioritised, to use keyboard take the mouse away from the window and use keyboard

(~30 minutes)
Changed powerup drops to be based on bricks broken, everytime the player breaks a brick there is a 30% chance for a powerup
to spawn.

(~1 and 1/2 hours)
Implemented a sticky ball powerup allowing the ball to stick to the paddel whilst active and the player to be able
to shoot the ball with left mouse click or be automatically let go once the timer reaches 0.