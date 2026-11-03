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
<Add information to this section about the time you've taken for this task along with a professional changelist.>

26/10/2026 16:00-17:00 : Initial pull request. Read through the code and created a list of things that I want to do. Will probably have to look at some SFML documentation to implement some of this.
27/10/2026 16:00-17:30 : Implemented basic Camera Manager that offsets the camera when the ball hits a wall.
27/10/2026 20:00-22:00 : Making no headway. Tried implementing a better way of organizing the powerups but it didn't work so I scrapped it.
27/10/2026 22:00-22:30 : Created a basic effects class to hopefully work on tomorrow to create a better way of managing active powerups.

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!
