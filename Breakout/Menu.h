#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
public:
	Menu(sf::RenderWindow* window);

public:
	void initialize();
	void update();
	void render();
	void HandleEvent(const sf::Event& event);
	bool shouldStartGame() const;

private:
	sf::RenderWindow* _window;

	float windowWidth;
	float windowHeight;
	int selectedIndex = 2;
	bool startGame;

	sf::Text title;
	sf::Font titleFont;

	sf::Text menuText[2];
	sf::Font textFont;
};