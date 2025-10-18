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
	_powerupText.setPosition(425, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_powerupTimerBG.setPosition(350, 50);
	_powerupTimerBG.setSize(sf::Vector2f(250, 20));
	_powerupTimerBG.setFillColor(sf::Color::Transparent);

	_powerupTimer.setPosition(355, 55);
	_powerupTimer.setSize(sf::Vector2f(240, 10));
	_powerupTimer.setFillColor(sf::Color::Transparent);
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
		_powerupTimerBG.setFillColor(paddleEffectsColour);
		_powerupTimer.setSize(sf::Vector2f(240.0f * (powerup.second / 5.0f), 10.0f));
		_powerupTimer.setFillColor(sf::Color::Black);
		break;
	case smallPaddle:
		_powerupText.setString("small");
		_powerupText.setFillColor(paddleEffectsColour);
		_powerupTimerBG.setFillColor(paddleEffectsColour);
		_powerupTimer.setSize(sf::Vector2f(240.0f * (powerup.second / 5.0f), 10.0f));
		_powerupTimer.setFillColor(sf::Color::Black);
		break;
	case slowBall:
		_powerupText.setString("slow");
		_powerupText.setFillColor(ballEffectsColour);
		_powerupTimerBG.setFillColor(ballEffectsColour);
		_powerupTimer.setSize(sf::Vector2f(240.0f * (powerup.second / 5.0f), 10.0f));
		_powerupTimer.setFillColor(sf::Color::Black);
		break;
	case fastBall:
		_powerupText.setString("fast");
		_powerupText.setFillColor(ballEffectsColour);
		_powerupTimerBG.setFillColor(ballEffectsColour);
		_powerupTimer.setSize(sf::Vector2f(240.0f * (powerup.second / 5.0f), 10.0f));
		_powerupTimer.setFillColor(sf::Color::Black);
		break;
	case fireBall:
		_powerupText.setString("fire");
		_powerupText.setFillColor(extraBallEffectsColour);
		_powerupTimerBG.setFillColor(extraBallEffectsColour);
		_powerupTimer.setSize(sf::Vector2f(240.0f * (powerup.second / 5.0f), 10.0f));
		_powerupTimer.setFillColor(sf::Color::Black);
		break;
	case none:
		_powerupText.setString("");
		_powerupTimer.setFillColor(sf::Color::Transparent);
		_powerupTimerBG.setFillColor(sf::Color::Transparent);
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
	_window->draw(_powerupTimerBG);
	_window->draw(_powerupTimer);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}