#pragma once
#include <SFML/Graphics.hpp>

class CameraManager {
public:
	CameraManager(sf::RenderWindow* window);
	void update(float dt);
	void screenShake(float trauma, float duration_ms);

private:
	// SFML window and view
	sf::RenderWindow* _window;
	sf::View _view;

	// View center
	sf::Vector2f _center;

	// Screen duration
	sf::Time _shakeStart;
	sf::Time _shakeDuration;

	// Screen trauma on shake
	float _trauma;
};