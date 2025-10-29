#include "Button.h"

Button::Button(sf::RenderWindow* w, STATES* state)
{
	_window = w;
	_state = state;
}

Button::~Button()
{
}

void Button::setupButton(std::string string, sf::Color textColor, int textSize, float textOffsetX, sf::Color RectColor,sf::Color hoverColor, sf::Vector2f pos, sf::Vector2f size, BUTTON_ACTIONS action)
{
	_text.setString(string);
	_text.setCharacterSize(textSize);
	_text.setFillColor(textColor);
	_text.setPosition(sf::Vector2f(pos.x+textOffsetX,pos.y));

	_rectangle.setPosition(pos);
	_rectangle.setFillColor(RectColor);
	_rectangle.setSize(size);

	_font.loadFromFile("font/montS.ttf");
	_text.setFont(_font);

	_normColor = RectColor;
	_hoverColor = hoverColor;

	_position = pos;
	_size = size;

	_action = action;
}

void Button::update()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);

	//std::string textString = std::to_string(mousePos.x) + "  " + std::to_string(mousePos.y);
	//_text.setString(textString);

	if (mousePos.x >= _position.x && mousePos.x <= _position.x + _size.x && mousePos.y >= _position.y && mousePos.y <= _position.y + _size.y)
	{
		_rectangle.setFillColor(_hoverColor);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			switch (_action)
			{
			case BUTTON_ACTIONS::REPLAY:
			{
				*_state = STATES::RESET;
			}
			break;
			default:
			break;
			}
		}
	}
	else
	{
		_rectangle.setFillColor(_normColor);
	}


	
}

void Button::render()
{
	_window->draw(_rectangle);
	_window->draw(_text);
}
