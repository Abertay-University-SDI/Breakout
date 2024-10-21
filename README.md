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
0:10 - Fixed circular dependency error preventing game from starting
0:30 - Added a simple trail to follow the ball around the screen
1:00 - Added audio
1:35 - Added a new powerup, has a bug when hitting the paddle
1:45 - Parameterised the function which spawns a powerup
2:15 - Added screen shake when player loses life (forgot to commit here, in the same commit as game restart)
2:20 - Added the ability to restart the game as required
3:00 - Added the progress bar for the powerups

https://www.sfml-dev.org/tutorials/2.6/audio-sounds.php
https://pixabay.com/sound-effects/search/retro%20games/
https://en.sfml-dev.org/forums/index.php?topic=27891.0
https://en.sfml-dev.org/forums/index.php?topic=4885.0