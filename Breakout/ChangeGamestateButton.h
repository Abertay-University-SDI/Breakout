#pragma once
#include "Button.h"

class ChangeGamestateButton : public Button
{
public:
	ChangeGamestateButton(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, int desiredGamestate, int buttonTextSize = 20, sf::String buttonText = "Button", sf::Color buttonTextColour = sf::Color::Black, sf::Color buttonColour = sf::Color::Cyan);

	virtual void PressedLogic() override;

	bool ShouldChangeGamestate();
	int GetRequiredGamestate();

protected:
	bool bShouldChangeGamestate;
	int _desiredGamestate;
};
