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
	PBmaxWidth = 100.f;
	PBself.setSize(sf::Vector2f(100.f, 50.f));
	PBself.setFillColor(sf::Color(50, 50, 50, 200));
	PBself.setPosition(800, 10);
	PBslef.setSize(sf::Vector2f(100.f, 50.f));
	PBslef.setFillColor(sf::Color::Cyan);
	PBslef.setPosition(PBself.getPosition());
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	if (powerup.first != activePU) {
		activePU = powerup.first;
		if (powerup.first = none) {
			PBmaxVal = powerup.second;
		}
	}
	float percent = powerup.second / PBmaxVal;
	switch (powerup.first)
	{
	case bigPaddle:
		PBslef.setSize(sf::Vector2f(PBmaxWidth * powerup.second, 50.f));
		PBslef.setFillColor(paddleEffectsColour);
		_powerupText.setString("Big");
		_powerupText.setFillColor(sf::Color(250, 20, 20, 200));
		break;
	case smallPaddle:
		PBslef.setSize(sf::Vector2f(PBmaxWidth * percent, 50.f));
		PBslef.setFillColor(paddleEffectsColour);
		_powerupText.setString("Small");
		_powerupText.setFillColor(sf::Color(250, 20, 20, 200));
		break;
	case slowBall:
		PBslef.setSize(sf::Vector2f(PBmaxWidth * percent, 50.f));
		PBslef.setFillColor(ballEffectsColour);
		_powerupText.setString("Slow");
		_powerupText.setFillColor(sf::Color(250, 20, 20, 200));
		break;
	case fastBall:
		PBslef.setSize(sf::Vector2f(PBmaxWidth * percent, 50.f));
		PBslef.setFillColor(ballEffectsColour);
		_powerupText.setString("Fast");
		_powerupText.setFillColor(sf::Color(250, 20, 20, 200));
		break;
	case fireBall:
		PBslef.setSize(sf::Vector2f(PBmaxWidth * percent, 50.f));
		PBslef.setFillColor(extraBallEffectsColour);
		_powerupText.setString("Fire");
		_powerupText.setFillColor(sf::Color(250, 20, 20, 200));
		break;
	case none:
		_powerupText.setString("");
		PBself.setSize(sf::Vector2f(0.f, 0.f));
		PBslef.setSize(sf::Vector2f(0.f, 0.f));
		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(PBself);
	_window->draw(PBslef);
	_window->draw(_powerupText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}