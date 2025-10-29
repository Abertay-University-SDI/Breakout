#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "CONSTANTS.h"

class Button
{
public:
	Button(sf::RenderWindow* w, STATES* state);
	~Button();

	void setupButton(std::string string, sf::Color textColor,int textSize,float textOffsetX, sf::Color RectColor, sf::Color hoverColor, sf::Vector2f pos, sf::Vector2f size, BUTTON_ACTIONS action);
	void update();
	void render();

private:
	sf::RenderWindow* _window;
	STATES* _state;

	sf::Text _text;
	sf::Font _font;
	sf::RectangleShape _rectangle;
	sf::Color _normColor;
	sf::Color _hoverColor;
	sf::Vector2f _position;
	sf::Vector2f _size;

	BUTTON_ACTIONS _action;
};

