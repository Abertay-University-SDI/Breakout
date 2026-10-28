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

Feature Planning 30 mins
   - Plan how split ball will work and plan the ball manager

Split-Ball Powerup: 2hr 30 m 
   - When Ball collides with anything, the ball will split. Up to five splits are allowed and a split happens on the main ball. Split balls are a different colour from the main ball and also move slower
   
Changes:
 - Added Ball Manager class for management of Balls. Balls are stored in a ordered map sorted by a unique ID generated when a ball is created.
 - Ball Manager can create, mark a ball for death, removed marked balls and is also responsible for updating and rendering the balls.
 - Added SplitBall powerup to the powerup manager.
 - Added several Getter and Setter methods into the ball class for extra utility in getting a balls direction, position etc.
 - Ball colour can be changed rather than it being hardcoded to cyan.
 - A ball can now be marked as the or A main ball. Main ball will involve the loss of a life if it hits the bottom. can be used to make the split off balls also main balls (might make it a bit hard to play though).
 - Removed Fast Ball as it is horrible.
---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again
* 2026 - Liam Added Cool Powerup. Also Removed Fast-Ball

---

Curse you, fast ball! (its gone now...)
