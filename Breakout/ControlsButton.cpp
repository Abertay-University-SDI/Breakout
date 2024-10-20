#include "ControlsButton.h"

ControlsButton::ControlsButton(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, InputManager* inputManager, int buttonTextSize, int currentControlsTextSize, sf::String buttonText, sf::Color buttonTextColour, sf::Color buttonColour) : Button(window, buttonPosition, buttonSize, font, buttonTextSize, buttonText, buttonTextColour, buttonColour), _inputManager(inputManager)
{
	sf::Vector2f buttonTextPosition = _buttonText.getPosition();
	_currentControlsText.setPosition(sf::Vector2f(buttonTextPosition.x, buttonTextPosition.y + 50));
	_currentControlsText.setFillColor(buttonTextColour);
	_currentControlsText.setFont(_font);
	_currentControlsText.setCharacterSize(currentControlsTextSize);
}

void ControlsButton::PressedLogic()
{
	Button::PressedLogic();

	_inputManager->SwapControlScheme();
}

void ControlsButton::update(float dt)
{
	Button::update(dt);

	if (_inputManager->IsKeyboardInputActive())
	{
		_currentControlsText.setString("Current Controls: Keyboard");
	}
	else
	{
		_currentControlsText.setString("Current Controls: Mouse");
	}
}

void ControlsButton::render()
{
	Button::render();

	_window->draw(_currentControlsText);
}


