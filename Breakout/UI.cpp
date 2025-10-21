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
	//_powerupText.setCharacterSize(30);
	//_powerupText.setPosition(800, 10);
	//_powerupText.setFillColor(sf::Color::Cyan);
	//_font.loadFromFile("font/montS.ttf");
	//_powerupText.setFont(_font);

	// Countdown timer bar replaces the text version.
	_powerupBar.setSize(sf::Vector2f(200.0f, 20.0f)); 
	_powerupBar.setPosition(800, 10); 
	_powerupBar.setFillColor(sf::Color::Cyan);

}

UI::~UI()
{
}

void UI::updatePowerupBar(std::pair<POWERUPS, float> powerup)
{
	switch (powerup.first)
	{
	case bigPaddle:
		_powerupBar.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		_powerupBar.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		_powerupBar.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		_powerupBar.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		_powerupBar.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupBar.setSize(sf::Vector2f(0, 20)); // hide bar
		_powerupDuration = 0.0f;
		return;
	}

	// Set full duration once.
	if (powerup.second > _powerupDuration)
		_powerupDuration = powerup.second;

	// Scale bar width based on remaining time.
	float percent = powerup.second / _powerupDuration;
	_powerupBar.setSize(sf::Vector2f(200.0f * percent, 20.0f));
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupBar);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}