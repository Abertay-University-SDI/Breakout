#pragma once
#include "Button.h"
#include "InputManager.h"

class ControlsButton : public Button
{
public:
	ControlsButton(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, InputManager* inputManager, int buttonTextSize = 20, int currentControlsTextSize = 12, sf::String buttonText = "Button", sf::Color buttonTextColour = sf::Color::Black, sf::Color buttonColour = sf::Color::Cyan);

	virtual void PressedLogic() override;
	virtual void update(float dt) override;
	virtual void render() override;

protected:
	InputManager* _inputManager;

	sf::Text _currentControlsText;
};
