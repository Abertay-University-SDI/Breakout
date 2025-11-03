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

	//Powerup progress bar setup
	_powerupBarMaxWidth = 200.f;
	_maxPowerupTime = 0.f;
	_currentPowerupTime = 0.f;

	_powerupBarBackground.setSize(sf::Vector2f(_powerupBarMaxWidth, 20.f));
	_powerupBarBackground.setFillColor(sf::Color::White);
	_powerupBarBackground.setOutlineColor(sf::Color::Cyan);
	_powerupBarBackground.setOutlineThickness(2.f);
	_powerupBarBackground.setPosition(790.f, 50.f);

	_powerupBarFill.setSize(sf::Vector2f(_powerupBarMaxWidth, 20.f));
	//_powerupBarFill.setFillColor(sf::Color::Green);
	_powerupBarFill.setPosition(790.f, 50.f);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	if (_maxPowerupTime == 0.f)
	{
		_maxPowerupTime = powerup.second;
	}

	_currentPowerupTime = powerup.second;

	float powerupProgress = _currentPowerupTime / _maxPowerupTime;
	powerupProgress = std::max(0.f, std::min(1.f, powerupProgress));

	_powerupBarFill.setSize(sf::Vector2f(_powerupBarMaxWidth * powerupProgress, 20.f));

	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_powerupBarFill.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		_powerupBarFill.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_powerupBarFill.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_powerupBarFill.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		_powerupBarFill.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		_powerupBarFill.setSize(sf::Vector2f(0.f, 20.f));
		
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
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
	_window->draw(_powerupBarBackground);
	_window->draw(_powerupBarFill);
}