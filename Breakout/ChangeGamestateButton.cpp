#include "ChangeGamestateButton.h"

ChangeGamestateButton::ChangeGamestateButton(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, int desiredGamestate, int buttonTextSize, sf::String buttonText, sf::Color buttonTextColour, sf::Color buttonColour) : Button(window, buttonPosition, buttonSize, font, buttonTextSize, buttonText, buttonTextColour, buttonColour), bShouldChangeGamestate(false), _desiredGamestate(desiredGamestate)
{
}

void ChangeGamestateButton::PressedLogic()
{
	Button::PressedLogic();

	bShouldChangeGamestate = true;
}

bool ChangeGamestateButton::ShouldChangeGamestate()
{
	return bShouldChangeGamestate;
}

int ChangeGamestateButton::GetRequiredGamestate()
{
	return _desiredGamestate;
}
