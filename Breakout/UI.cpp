#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	// powerup bar properties
	powerupBar.setSize(sf::Vector2f(0,20));
	powerupBar.setPosition(800, 50);
	powerupBar.setFillColor(sf::Color::Magenta);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	switch (powerup.first)
	{
	case bigPaddle:
		_powerupText.setString("big");
		_powerupText.setFillColor(paddleEffectsColour);
		powerupBar.setSize(sf::Vector2f(powerup.second * 20, 20));
		break;
	case smallPaddle:
		_powerupText.setString("small");
		_powerupText.setFillColor(paddleEffectsColour);
		powerupBar.setSize(sf::Vector2f(powerup.second * 20, 20));
		break;
	case slowBall:
		_powerupText.setString("slow");
		_powerupText.setFillColor(ballEffectsColour);
		powerupBar.setSize(sf::Vector2f(powerup.second * 20, 20));
		break;
	case fastBall:
		_powerupText.setString("fast");
		_powerupText.setFillColor(ballEffectsColour);
		powerupBar.setSize(sf::Vector2f(powerup.second * 20, 20));
		break;
	case fireBall:
		_powerupText.setString("fire");
		_powerupText.setFillColor(extraBallEffectsColour);
		powerupBar.setSize(sf::Vector2f(powerup.second * 20, 20));
		break;
	case none:
		_powerupText.setString("");
		
		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);
	_window->draw(powerupBar);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}
