# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

## Controls

A/D or Left/Right to move the paddle left and right.
P to pause.
R to restart on game over or level complete.

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

<Add information to this section about the time you've taken for this task along with a professional changelist.>

* Game can be restarted after game over. Time taken: 15 minutes.
* Game over stats, including number of bricks remaining, and highest number of bricks broken across all playthroughs. Time taken: 13 minutes.
* Progress bar that ticks down based on current power-up. Time taken: 38 minutes.
* UI text colour and size redone for consistency. Time taken: 2 minutes.
* Game can be restarted after level completed. Time taken: 2 minutes.
* Screen shakes on life lost. Time taken:  1 hour and 2 minutes.
* Fixed ball appearing on game over. Time taken: 3 minutes.
* Added new powerup type. A health powerup that will give back one life out of three when hit by paddle. Time taken: 55 minutes.
* Added right/left key controls. Time taken: 3 minutes.
* Added new powerup type. A powerup which spawns a swarm of balls that will circulate the scene and when fallen, do not lose a life. Time taken: 1 hour and 44 minutes.

Total time taken working: 4 hours and 57 minutes.

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!