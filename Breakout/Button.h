#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	Button(sf::RenderWindow* window, sf::Vector2f buttonPosition, sf::Vector2f buttonSize);

	void update(float dt);
	void render();

	virtual void PressedLogic();

	bool IsButtonPressed();

protected:
	sf::RenderWindow* _window;
	sf::Vector2f _buttonPosition;
	sf::Vector2f _buttonSize;

	bool bIsButtonPressed = false;
};