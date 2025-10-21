#include "Menu.h"
#include <iostream>

Menu::Menu(sf::RenderWindow* window)
	: _window(window), windowWidth(static_cast<float>(window->getSize().x)),
	windowHeight(static_cast<float>(window->getSize().y)), startGame(false)
{

}

void Menu::initialize()
{
	std::cout << "Menu Init" << std::endl;
	startGame = false;



	titleFont.loadFromFile("font/title_text.ttf");
	title.setFont(titleFont);
	title.setCharacterSize(148);
	title.setString("BREAKOUT");
	title.setPosition(windowWidth / 2 - 250, windowHeight / 4);


	textFont.loadFromFile("font/menu_text.ttf");
	menuText[0].setFont(textFont);
	menuText[0].setCharacterSize(36);
	menuText[0].setString("Press SPACE to Start");
	menuText[0].setPosition(windowWidth / 2 - 120, windowHeight / 2);

	menuText[1].setFont(textFont);
	menuText[1].setCharacterSize(36);
	menuText[1].setString("Quit");
	menuText[1].setPosition(windowWidth / 2 - 10, windowHeight / 2 + 55);

}

void Menu::update()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);


	for (int i = 0; i < 2; i++)
	{
		for (int i = 0; i < 2; i++)
		{
			if (menuText[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
			{
				menuText[i].setFillColor(sf::Color::Red);
			}

			else
			{
				menuText[i].setFillColor(sf::Color::White);
			}
		}
	}
}

void Menu::HandleEvent(const sf::Event& event)
{
	if (!startGame)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (menuText[0].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
			{
				startGame = true;
			}

			else if (menuText[1].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
			{
				_window->close();
			}
		}


		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				startGame = true;
			}
		}
	}
}

void Menu::render()
{
	_window->draw(title);
	_window->draw(menuText[0]);
	_window->draw(menuText[1]);
}

bool Menu::shouldStartGame() const
{
	return startGame;
}