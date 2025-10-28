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
		newLife.setFillColor(lifeColor);
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(650, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);
}

UI::~UI()
{
}


void UI::updatePowerupText(const std::vector<std::shared_ptr<BaseEffect>> effects)
{
	std::ostringstream oss;

	for(auto& effect: effects)
	{
		oss << effect->GetName() << ": ";
		oss << std::fixed << std::setprecision(2) << effect->getDurationLeft();
		oss << '\n';
	}

	_powerupText.setString(oss.str());

	//switch (powerup.first)
	//{
	//case bigPaddle:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("big " + oss.str());
	//	_powerupText.setFillColor(paddleEffectsColour);
	//	break;
	//case smallPaddle:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("small " + oss.str());
	//	_powerupText.setFillColor(paddleEffectsColour);
	//	break;
	//case slowBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("slow " + oss.str());
	//	_powerupText.setFillColor(ballEffectsColour);
	//	break;
	//case fastBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("fast " + oss.str());
	//	_powerupText.setFillColor(ballEffectsColour);
	//	break;
	//case fireBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("fire " + oss.str());
	//	_powerupText.setFillColor(extraBallEffectsColour);
	//	break;
	//case none:
	//	_powerupText.setString("");
	//	
	//	break;
	//}
}

void UI::lifeLost(int lives)
{
	for (int i = 0; i < _lives.size(); ++i)
	{
		_lives[ _lives.size() - i - 1].setFillColor(i < lives ? lifeColor : lostLifeColor);
	}
}

void UI::render()
{
	_window->draw(_powerupText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}