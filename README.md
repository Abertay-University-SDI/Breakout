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

<27/10/2026, 4 hours>
-Looked over existing code
-Began creating a multiball powerup
-Added multiball to PowerupManager
-Added multiball functionlity to ball class
-Added spawning of multiball in GameManager class (WIP)
-Changed spawning mechanic of multiball to spawn in GM initialise
-Changed spawning back to original method
-Created separate multiball class inheriting from ball class
-Changed multiball to include psuedo-invincibility

<28/10/2026, 1 hour 30 minutes>
-Re-read code added on previous day
-Removed and deleted separate multiball class from project
-Changed spawning of multiball to spawn in GM initialise
-Added functions in ball class to be called for multiball
   -setDirection
   -setMultiColor
   -setMultiPosition
   -setMultiVelocity

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!
