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
	_powerupText.setPosition(625, 15);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_livesText.setCharacterSize(30);
	_livesText.setPosition(200, 15);
	_livesText.setFillColor(sf::Color::Cyan);
	_livesText.setFont(_font);
	_livesText.setString("LIVES");

	_emptyProgressbar.setPosition(750, 20);
	_emptyProgressbar.setFillColor(sf::Color::Transparent);
	_emptyProgressbar.setOutlineThickness(4.0f);
	_emptyProgressbar.setOutlineColor(sf::Color::Cyan);
	_emptyProgressbar.setSize(sf::Vector2f(225.f, 30.0f));

	_powerupProgressbar.setPosition(750, 20);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{

	switch (powerup.first)
	{
	case bigPaddle:
		_powerupText.setString("BIG");
		_powerupProgressbar.setFillColor(paddleEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
		break;
	case smallPaddle:
		_powerupText.setString("SMALL");
		_powerupProgressbar.setFillColor(paddleEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
		break;
	case slowBall:
		_powerupText.setString("SLOW");
		_powerupProgressbar.setFillColor(ballEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
		break;
	case fastBall:
		_powerupText.setString("FAST");
		_powerupProgressbar.setFillColor(ballEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
		break;
	case fireBall:
		_powerupText.setString("FIRE");
		_powerupProgressbar.setFillColor(extraBallEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
		break;
	case multiBall:
		_powerupText.setString("MULTI");
		_powerupProgressbar.setFillColor(ballEffectsColour);
		_powerupProgressbar.setSize(sf::Vector2f(powerup.second * 45.0f, 30.0f));
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

void UI::lifeGained(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Red);
}

void UI::render()
{
	_window->draw(_emptyProgressbar);
	_window->draw(_powerupText);
	_window->draw(_livesText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
	_window->draw(_powerupProgressbar);
}