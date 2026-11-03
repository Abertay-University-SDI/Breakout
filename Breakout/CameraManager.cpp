#include "CameraManager.h"

#include <cmath>

CameraManager::CameraManager(sf::RenderWindow* window)
	: _window(window), _shakeAnimation(), _shakeRNG(std::random_device{}())
{
	_view = _window->getView();
	
	// Compute the view centre
	sf::Vector2u size = _window->getSize();
	_centre = sf::Vector2f(size.x / 2, size.y / 2);
	_view.setCenter(_centre);
}

void CameraManager::shake(float magnitude, float duration)
{
	//_currentDuration = duration;

	//// magnitude is added to current camera shake magnitude so multiple calls increase the shake.
	//_currentMagnitude += magnitude;

	_shakeAnimation.currentDuration = 0.f;
	_shakeAnimation.maxDuration = duration;
	// magnitude is added to current camera shake magnitude so multiple calls increase the shake.
	_shakeAnimation.currentMagnitude += magnitude;
}

void CameraManager::update(float dt)
{
	/*if (_currentDuration <= 0.f) { return; }*/

	if (_shakeAnimation.currentDuration >= _shakeAnimation.maxDuration) { return; }

	// Do shake rotation later...

	// Compute the shake offset
	/*float t = 1 - (_shakeAnimation.currentDuration / _shakeAnimation.maxDuration);
	float currentMaxMagnitude = std::lerp(0.0f, _shakeAnimation.currentMagnitude, t);*/	// We want the range of the random magnitude to diminish over time.

	std::uniform_real_distribution<float> magDist(
		CAMERA_SHAKE_OFFSET * -_shakeAnimation.currentMagnitude,
		CAMERA_SHAKE_OFFSET * _shakeAnimation.currentMagnitude
	);

	sf::Vector2f offset;
	offset.x = magDist(_shakeRNG);
	offset.y = magDist(_shakeRNG);

	// Apply the camera shake to the view
	_view.setCenter(_centre + offset);
	_window->setView(_view);

	// Update camera shake time
	_shakeAnimation.currentDuration += dt;

	// Decrease trauma parameter depending on time (squared)
	// Was going to do it a different way to Pierre Lefebvre's (2022). But std::lerp doesn't exist in C++ 17 >:(
	float playback = _shakeAnimation.currentDuration / _shakeAnimation.maxDuration;
	_shakeAnimation.currentMagnitude *= 1.0 - playback * playback;
}