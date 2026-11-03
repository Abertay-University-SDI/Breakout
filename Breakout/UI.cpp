#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>
#include <thread>
#include <chrono>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Color(205, 180, 219));
		newLife.setOutlineColor(sf::Color::Color(162, 210, 255));
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Color(162, 210, 255));
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	_comboText.setCharacterSize(50);
	_comboText.setPosition(900, 700);
	_comboText.setFillColor(sf::Color::Color(162, 210, 255));
	_font.loadFromFile("font/CarterOne-Regular.ttf");
	_comboText.setFont(_font);

	_newLifeText.setCharacterSize(50);
	_newLifeText.setPosition(800, 700);
	_newLifeText.setFillColor(sf::Color::Color(162, 210, 255));
	_newLifeText.setFont(_font);

	_shakeValText.setCharacterSize(50);
	_shakeValText.setPosition(20, 700);
	_shakeValText.setFillColor(sf::Color::Color(162, 210, 255));
	_shakeValText.setFont(_font);
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

void UI::updateComboText(std::string combo, int size)
{
	_comboText.setCharacterSize(size);

	_comboText.setFillColor(sf::Color::Color(162 - (size - 50), 210 - (size - 50), 255 - (size - 50)));

	_comboText.setString(combo);
}

void UI::updateShakeValText(std::string shakeVal)
{
	_shakeValText.setString(shakeVal);
}

void UI::lifeLost(int lives)
{
	if (lives < 3)
	{
		_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
	}
	else
	{
		_lives.pop_back();
	}
}

void UI::render()
{
	_window->draw(_powerupText);
	_window->draw(_comboText);
	//_window->draw(_shakeValText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}

void UI::lifeGain(int lives)
{
	sf::CircleShape newLife;
	newLife.setFillColor(sf::Color::Color(205, 180, 219));
	newLife.setOutlineColor(sf::Color::Color(162, 210, 255));
	newLife.setOutlineThickness(4.0f);
	newLife.setRadius(LIFE_RADIUS);
	newLife.setPosition((LIFE_RADIUS * 2 + LIFE_PADDING) * lives, LIFE_PADDING);
	_lives.push_back(newLife);
}