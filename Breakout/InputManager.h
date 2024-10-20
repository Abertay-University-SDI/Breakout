#pragma once

#include "Paddle.h"

class InputManager
{
public:
	InputManager(sf::RenderWindow* window, Paddle* paddle);

	void update(float dt);

private:
	sf::RenderWindow* _window;
	Paddle* _paddle;

	sf::Vector2u _windowSize;
};
