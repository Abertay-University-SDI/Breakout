#include "InputManager.h"
#include <iostream>

InputManager::InputManager(sf::RenderWindow* window, Paddle* paddle) 
	: _window(window), _paddle(paddle), _windowSize(window->getSize())
{
}

void InputManager::update(float dt)
{
	// Will include this option when deciding between mouse and keyboard controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (_paddle)
		{
			_paddle->moveRight(dt);
		}
	}
	 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (_paddle)
		{
			_paddle->moveLeft(dt);
		}
	}

	sf::Vector2i RelativeMousePosition = sf::Mouse::getPosition(*_window);

	// Debug lines
	std::cout << RelativeMousePosition.x << " " << RelativeMousePosition.y << " " << "Size of window: " << _window->getSize().x << " " << _window->getSize().y << std::endl;
}
