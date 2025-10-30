#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include <vector>

class ScreenShake
{
public:

	sf::Vector2f shakeOffset = sf::Vector2f(0, 0);
	float shakeDuration = 0.2f;
	float shakeMagnitude = 2.5f;
	void update();
	void render(sf::RenderWindow& _window);
	void startShake();
};

