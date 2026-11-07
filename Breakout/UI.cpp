#include "UI.h"
#include "GameManager.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace
{
	// Constants for the powerup bar
	const float powerupBarX = 800.0f;
	const float powerupBarY = 50.0f;
	const float powerupBarWidth = 185.0f;
	const float powerupBarHeight = 20.0f;
}

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

	///INITIALIZE POWERUP BAR

	//Powerup bar background
	_powerupBarBackground.setSize({powerupBarWidth, powerupBarHeight});
	_powerupBarBackground.setPosition(powerupBarX, powerupBarY);
	_powerupBarBackground.setFillColor(sf::Color(50, 50, 50, 200));

	//Powerup bar
	_powerupBar.setSize({ 0.f, powerupBarHeight });
	_powerupBar.setPosition(powerupBarX, powerupBarY);
}

UI::~UI()
{
}

void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	// Update the powerup text
	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		break;
	}

	// Update the powerup bar
	// If there is no powerup, reset the bar
	if (powerup.first == none)
	{
		_powerupBarMaxTime = 0.f;
		_powerupBar.setSize({ 0.f, powerupBarHeight });
	}
	else
	{
		// If the powerup has changed, update the bar
		if (powerup.first != _lastPowerup || powerup.second > _powerupBarMaxTime)
			_powerupBarMaxTime = powerup.second;		
		
		//Recalculate the fraction of the bar to fill based on the remaining time and the max time
		const float fraction = (_powerupBarMaxTime > 0.f)
			? std::clamp(powerup.second / _powerupBarMaxTime, 0.f, 1.f) : 0.f;

		_powerupBar.setSize({ powerupBarWidth * fraction, powerupBarHeight });
		_powerupBar.setFillColor(_powerupText.getFillColor());
	}

	// Set last powerup to current powerup
	_lastPowerup = powerup.first;
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);

	// Draw powerup bar if there is a powerup in effect
	if (!_powerupText.getString().isEmpty())
	{
		_window->draw(_powerupBarBackground);
		_window->draw(_powerupBar);
	}

	// Draw lives
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}