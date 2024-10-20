#include "Button.h"
#include <iostream>

Button::Button(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, int buttonTextSize, sf::String buttonText, sf::Color buttonTextColour, sf::Color buttonColour)
	: _window(window), _buttonPosition(buttonPosition), _buttonSize(buttonSize), bIsButtonPressed(false), _buttonColour(buttonColour), pressedHoldStartTime(0.3f), pressedHoldTimer(pressedHoldStartTime)
{
	_sprite.setFillColor(_buttonColour);
	_sprite.setPosition(_buttonPosition);
	_sprite.setSize(_buttonSize);

	_buttonText.setString(buttonText);
	_buttonText.setPosition(buttonPosition);
	_buttonText.setFillColor(buttonTextColour);
	_buttonText.setCharacterSize(buttonTextSize);

	_font = font;
	_buttonText.setFont(_font);

}

void Button::update(float dt)
{
	if (!bIsButtonPressed)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i MousePosition = sf::Mouse::getPosition(*_window);
			if (MousePosition.x > _buttonPosition.x && MousePosition.x < _buttonPosition.x + _buttonSize.x)
			{
				if (MousePosition.y > _buttonPosition.y && MousePosition.y < _buttonPosition.y + _buttonSize.y)
				{
					PressedLogic();
					pressedHoldTimer = pressedHoldStartTime;
				}
			}

			std::cout << MousePosition.x << " " << MousePosition.y << " Button Position: " << _buttonPosition.x << " " << _buttonPosition.y << std::endl;
		}
	}
	else
	{
		pressedHoldTimer -= dt;
		if (pressedHoldTimer <= 0)
		{
			ResetButton();
		}
	}
}

void Button::render()
{
	_window->draw(_sprite);
	_window->draw(_buttonText);
}

void Button::PressedLogic()
{
	bIsButtonPressed = true;
}

void Button::ResetButton()
{
	bIsButtonPressed = false;
}

bool Button::IsButtonPressed()
{
	return bIsButtonPressed;
}
