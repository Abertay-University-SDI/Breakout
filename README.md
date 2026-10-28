# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

You are to spend between three and eight hours improving this simple Breakout implementation in a way to best demonstrate your capabilities as a games programmer. 

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* Add an actual game loop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball, brick-tracking ball)
    * Note: smallPaddle is too simple to be impressive.
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as Ollama

# Time Details and Changelist
_TO DO_

<Add information to this section about the time you've taken for this task along with a professional changelist.>
List of changes
commit 1
-Added Audio manager class Time Taken: 1.5 hours
-Added new power up extraball Time Taken: 0.5 hours
-Added list of Balls for extra Balls Time Taken: 10 minutes
-Added Parralax background, time taken: 1.5 hours
-Increased paddle Speed Time Taken:5 minutes
-Changed BrickManager to set colour based on Hitpoints Time Taken: 0.5 hours
-Changed bricks to have hitpoints and access them Time Taken: 0.25hours
-Added folder for assets and sounds Time Taken: 5 minutes
-Added sounds and images Time Taken: 15 minutes
-Changed gamemanager to include nextLevel + countdown Time Taken:0.25 hours
Changed Balls constructor to take in colour for differentiating between balls Time Taken: 10 minutes
updated game manager to use the new constructor Time Taken: 5 minutes
updated ball.cpp to update to the correct colour after power ups Time Taken: 10 minutes
total time:5.5 hours
-
-
---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!