#include "InputManager.h"
#include <iostream>

InputManager::InputManager(sf::RenderWindow* window, Paddle* paddle)
	: _window(window), _paddle(paddle), _windowSize(window->getSize()), movementBufferSize(2.0f), bIsKeyboardInputActive(false)
{
}

void InputManager::update(float dt)
{
	if (bIsKeyboardInputActive)
	{
		UpdateKeyboard(dt);
	}
	else
	{
		UpdateMouse(dt);
	}
}

void InputManager::UpdateKeyboard(float dt)
{
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
}

void InputManager::UpdateMouse(float dt)
{
	_windowSize = _window->getSize();

	int MousePositionX = sf::Mouse::getPosition(*_window).x;
	if (MousePositionX > 0 && MousePositionX <= _windowSize.x)
	{
		// Check if we should move to the right, based on mouse position and buffer
		float PaddlePositionX = _paddle->getPosition().x;
		if (PaddlePositionX > MousePositionX + movementBufferSize)
		{
			_paddle->moveLeft(dt);
		}
		else if (PaddlePositionX < MousePositionX - movementBufferSize)
		{
			_paddle->moveRight(dt);
		}
	}
}

void InputManager::SwapControlScheme()
{
	bIsKeyboardInputActive = !bIsKeyboardInputActive;
}

bool InputManager::IsKeyboardInputActive()
{
	return bIsKeyboardInputActive;
}
