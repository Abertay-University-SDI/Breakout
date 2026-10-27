#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape
{
public:
	Button(sf::RenderWindow* window);
	void handleInput();
	sf::Text* getText();
	void render();
	bool getActive();
	void setActive(bool active);
	bool isClicked();

private:
	bool _active;
	bool _keyPressed;
	bool _clicked;
	sf::Text _text;
	sf::RenderWindow* _window;
};

