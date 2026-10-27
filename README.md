# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D to move the paddle right and left.
Hold LMB to move the paddle to the mouse.
P to pause.
R to restart after game over.
Enter to start the next level.

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
26 Oct 2026 - 2.5 hrs
27 Oct 2026 - 3 hrs
Overall: 5.5 hrs

Changelog:
* Fixed issues with original project files
* Changed manual memory management to use smart pointers
* Organised all constants
* Fixed a bug with ball speed
* Small fix of paddle sizing
* Changed ball-brick collision to rect-circle and removing every brick the ball hits
* Mouse position controlling wired
* Implemented a game loop
* Implemented the leaderboard

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!
