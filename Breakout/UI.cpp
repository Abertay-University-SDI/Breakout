#include <sstream>
#include <iostream>
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
	_powerupText.setPosition(400, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_progressBarBack.setPosition(400, 50);
	_progressBarBack.setSize(sf::Vector2f(400, 30));
	_progressBarBack.setFillColor(sf::Color::Transparent);
	
	_progressBarFill.setPosition(405, 60);
	_progressBarFill.setSize(sf::Vector2f(390, 20));
	_progressBarFill.setFillColor(sf::Color::Transparent);

}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	//std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big");
		_powerupText.setFillColor(paddleEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case smallPaddle:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small");
		_powerupText.setFillColor(paddleEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case slowBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow");
		_powerupText.setFillColor(ballEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case fastBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast");
		_powerupText.setFillColor(ballEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case fireBall:
		//oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire");
		_powerupText.setFillColor(extraBallEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case bigBall:
		_powerupText.setString("big ball");
		_powerupText.setFillColor(ballEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case smallBall:
		_powerupText.setString("small ball");
		_powerupText.setFillColor(ballEffectsColour);
		_progressBarBack.setFillColor(sf::Color::Cyan);
		_progressBarFill.setSize(sf::Vector2(390.f * (powerup.second / 5.0f), 10.f));
		_progressBarFill.setFillColor(sf::Color::Red);
		break;
	case none:
		_powerupText.setString("");
		_progressBarBack.setFillColor(sf::Color::Transparent);
		_progressBarFill.setFillColor(sf::Color::Transparent);
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
	_window->draw(_progressBarBack);
	_window->draw(_progressBarFill);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}