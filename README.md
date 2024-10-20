# Breakout

W Kavanagh. June Summer 2024

## controls

A/D to move the paddle right and left.
P to pause.

## Powerups

big/small paddle (blue)
fast/slow ball (fancy yellow)
fire ball (green)

# Tasklist

## Suggested fixes

* Fix the compiler issues in the code

## Suggested tasks

* Implement mouse input for pad
* Improved VFX (ball trail, paddle hit response, brick particle destruction)
* Better UI (progress bar rather than timer for countdown).
* GameLoop
* Better ball physics (Box2D)
* Leaderboards
* More ball types (e.g., multiball, sticky ball [where you shoot the ball from the paddle every time], tiny ball, big ball, brick-tracking ball)
* Sounds with increasing tone between bounces.
* Implement commentary with calls to an LLM such as LLama

# Time Details and Changelist
Time taken: ~5h 30m

- Created generic "Button.h" base class, capable of performing custom functionality when pressed.
- Expanded on "Button.h" class with two button classes, "ControlsButton.h" and "ChangeGamestateButton.h", both of which perform different functionality.
- Created "ButtonManager.h" class, capable of rendering and updating all buttons added.
- Created two classes, "PauseMenu.h" and "StartMenu.h", to allow for a start and pause menu in game.
- Created "InputManager.h" class, to allow the user to swap between keyboard and mouse controls.
- Fixed bug where PowerupBase had included it's child class as a header file, causing child class to not be able to inherit from PowerupBase due to it being undefined at that time.
