#include "Button.h"

Button::Button(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize)
	: _window(window), _buttonPosition(buttonPosition), _buttonSize(buttonSize)
{
}

void Button::update(float dt)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left));
	{

	}
}

void Button::render()
{
}

void Button::PressedLogic()
{

}

bool Button::IsButtonPressed()
{
	return bIsButtonPressed;
}
