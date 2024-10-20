#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Font font, int buttonTextSize = 20, sf::String buttonText = "Button", sf::Color buttonTextColour = sf::Color::Black, sf::Color buttonColour = sf::Color::Cyan);

	virtual void update(float dt);
	virtual void render();

	virtual void PressedLogic();

	void ResetButton();

	bool IsButtonPressed();

protected:
	sf::RenderWindow* _window;
	sf::Vector2f _buttonPosition;
	sf::Vector2f _buttonSize;

	sf::RectangleShape _sprite;
	sf::Color _buttonColour;

	sf::Font _font;
	sf::Text _buttonText;

	float pressedHoldStartTime;
	float pressedHoldTimer;

	bool bIsButtonPressed;
};