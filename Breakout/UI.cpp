#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>
#include <iostream>

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
	_powerupText.setPosition(550.f, 30.f);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);
	powerUpBarInit();
	_clock.restart();
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_showBar = true;
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_showBar = true;
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_showBar = true;
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_showBar = true;
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		_showBar = true;
		break;
	case multiBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("multi " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
	case none:
		_powerupText.setString("");
		_showBar = false;
		break;
	}
	
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::powerUpBarInit()
{
	_powerupBarBG.setSize(sf::Vector2f(bgX, bgY));
	_powerupBarBG.setFillColor(sf::Color::Cyan);
	_powerupBarBG.setPosition(700.f, 30.f);

	_powerupBar.setSize(sf::Vector2f(barX, barY));
	_powerupBar.setFillColor(sf::Color::Red);
	_powerupBar.setPosition(_powerupBarBG.getPosition() + sf::Vector2f(5.f, 5.f));
	
}

void UI::powerUpBarUpdate()
{
	if (_showBar)
	{
		sf::Time t = _clock.getElapsedTime();

		if(t.asSeconds() > 0.5)
		{
			_powerupBar.setSize(sf::Vector2f((_powerupBar.getSize().x) - 19, barY));
			std::cout << "Bar size: " << _powerupBar.getSize().x << std::endl;
			_clock.restart();
		}
	}
}


void UI::render()
{
	_window->draw(_powerupText);
	if (_showBar && _gameManager->lives != 0)
	{
		powerUpBarUpdate();
		_window->draw(_powerupBarBG);
		_window->draw(_powerupBar);
	}else
	{
		if(_powerupBar.getSize().x == 0.f)
		{
			std::cout << "Reseting Bar" << std::endl;
			_powerupBar.setSize(sf::Vector2f(barX, barY));
		}
	}
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}