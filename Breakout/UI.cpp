#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(int lives, GameManager* gameManager)
	: _gameManager(gameManager), _newLifeStar(4, 0.0f, 0.0f)
{
	_lifeCircle.setOutlineColor(sf::Color::Cyan);
	_lifeCircle.setOutlineThickness(4.0f);
	_lifeCircle.setRadius(LIFE_RADIUS);
	_newLifeStar.setFillColor(sf::Color::Red);
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);
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
}

void UI::setLives(int lives)
{
	_lives = lives;
}

void UI::setNewLifeFraction(float fraction) {
	_newLifeFraction = fraction;
}

void UI::update(float dt) {
	_newLifeStar.rotate(dt * 90.0f);
}

void UI::render(sf::RenderWindow& window)
{
	window.draw(_powerupText);
	for (int i = 0; i < INITIAL_LIVES; i++)
	{
		_lifeCircle.setPosition((LIFE_RADIUS * 2 + LIFE_PADDING) * (i + 1), LIFE_PADDING);
		_lifeCircle.setFillColor(i < _lives ? sf::Color::Red : sf::Color::Transparent);
		window.draw(_lifeCircle);
	}
	if (_newLifeFraction > 0) {
		_newLifeStar.setPosition((LIFE_RADIUS * 2 + LIFE_PADDING) * (_lives + 1) + LIFE_RADIUS, LIFE_PADDING + LIFE_RADIUS);
		_newLifeStar.setInnerRadius((0.2f + 0.3f * _newLifeFraction) * LIFE_RADIUS);
		_newLifeStar.setOuterRadius((0.4f + 0.6f * _newLifeFraction) * LIFE_RADIUS);
		window.draw(_newLifeStar);
	}
}