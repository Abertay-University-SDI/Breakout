# Breakout

W Kavanagh & N Merchant. Summer 2024 (last maintained, Oct 26)

A Lim Autumn 2026 (last maintained Oct 27) 
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
* Approx. 4 hours were spend on this, over the course of two days
---

### Change log

* Added scoring system
* Bricks have different health and score values
* Bricks change colour based on health
* Bricks no longer have a chance to double collide with the ball per frame
* Powerup text moved to centre of screen
* Added button component with mouse input
* Added restart button for game loss and game end

---

Curse you, fast ball!