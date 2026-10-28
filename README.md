# Breakout


Name: Morgan Daniels
Student Number: 2300399


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

---

### Change log
* 2025 - Naman made it harder
* 2026 - William made it easier again

---

Curse you, fast ball!


---


### Changes 

SESSION 1  - 2 HOURS
26/10/26 - 14:25 -16:25

- Updated the lives counter in UI - now we display text giving the number of balls left (and a little ball icon)
This allows us to later add powerup and other features that would take the live counter above 3 with UI that can easily describe this.

- Designed and begun implementation of a gambling system, allowing the player to press a key to bet a ball, and have a random (weighted) effect rolled and applied to the game state.


SESSION 2 - 3 HOURS
27/10/26 - 17:55 - 19:55 (then a break) 21:30-22:30 

- Implemented an early working gambling system - the player can press "G" at any point, have a life deducted, and have 1 of 2 weighted random effects rolled. Text on screen will report what happened, or if you cannot gamble.

- Minor changes to lives logic - now gameplay continues at "0", and instead will go to "-" when that life is lost, and the game is then over.

- Designed and began implementation of an overhaul to the powerups that will allow for multiple to be active at once - now, powerups (or the gambler) will add a string "tag" to a queue, and a manager will decode that into the effect that needs to be applied as a result.
 


SESSION 3 - 3 HOURS
28/10/26 9:00-12:00

- Finished the new effects system, allowing multiple effects at once. Added some effects to the gambler.

