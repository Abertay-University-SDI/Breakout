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

* Fix the compiler issues in the codeW



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



Adrian Herrero Redden - 2202936



-Fixed compiler error caused by circular dependency - 5 mins

-Added mouse control which can be toggled on and off with 'M' - 10 mins

-Implemented a handle input function to game manager to distinguish updates from inputs - 5 mins

-Added score tracker which increments on block hits and decrements on loss of life - 15 mins

-Life lost screen + game over - 30 mins

-Game can be replayed after a loss or win - 30 mins

-Game can be continued after a win with an increasing score until failure - 15 minutes

-Added high score that is displayed on screen - 15 minutes

-Fixed bug that caused lives visual to not change upon death after restarting game - 10 mins

-Fixed bug where powerups could be carried into the next level - 10 mins

-Added reset button to pause menu, moved reset functionality to its own function in game manager - 10 mins

-Added "beast Mode" on the pause menu - 20 mins







(185 mins)

