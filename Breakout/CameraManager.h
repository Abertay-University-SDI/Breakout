#pragma once

/* Camera Manager for adding camera shake to the game. */
/* This code uses Pierre Lefebvre's (2022) Camera class for inspiration */
/* Source: https://github.com/plfbvr/sfml-camera-shake */

/* Camera Shake Methods: https://www.davetech.co.uk/gamedevscreenshake */
/* Current Method: Random x/y Diminishing Magnitude */

#include <SFML/Graphics.hpp>
#include <random>

#define CAMERA_SHAKE_ANGLE 10.0f
#define CAMERA_SHAKE_OFFSET 20.0f

/* Define the Camera Shake */
struct CameraShake {
	/* Current time (updated during shake) */
	float currentDuration;
	
	/* Max length of the camera shake */
	float maxDuration;

	/* Max amount of camera shake that occurs (when current duration = 0) */
	float currentMagnitude;
};

class CameraManager
{
public:
	/* Constructor */
	CameraManager(sf::RenderWindow* window);

	/* Shake the camera for a given amount of violence and time. */
	void shake(float magnitude, float duration);

	/* Update the camera state. Shall be called in the Game Manager's update loop. */
	void update(float dt);

private:
	// SFML window for this camera.
	sf::RenderWindow* _window;
	// View associated with the window
	sf::View _view;
	// View centre
	sf::Vector2f _centre;

	CameraShake _shakeAnimation;
	std::mt19937 _shakeRNG; // Using mersenne twister like in PowerupManager to keep consistency.
};

