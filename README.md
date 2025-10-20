# Breakout

W Kavanagh \& N Merchant. Summer 2024

R Booth - October 2025


## Controls

- A/D to move the paddle right and left.
- P to pause.

## Powerups

- Big/small paddle (lemony)
- Fast/slow/big ball (blue)
- Fire ball (green)

# Tasklist

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

## Time Spent: 4 hours (Approx.)

## Changelists:

### Added
- Smooth screen shake for when player misses ball or breaks a block
- New powerup that will make the ball bigger for 5s
- New particle effect that explodes when bricks are destroyed
- Restart game if game is over (win or lose)
- Access to quit game via "ESC" key

### Changed
- Parameterised powerup spawn chance

### Fixed
- Compiler issue in "PowerupBase.h" due to an extra and unessesary header



