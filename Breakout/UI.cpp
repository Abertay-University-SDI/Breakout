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
}

UI::~UI()
{
}


void UI::updatePowerupText(std::vector<std::pair<POWERUPS, float>> powerup)
{
	
	_powerupText.setString("");
	if (powerup.size() != 0) {

		for (int i = 0; i < powerup.size(); i++) {
			std::ostringstream oss;
			std::string text = "";

			switch (powerup[i].first)
			{
			case bigPaddle:
				oss << std::fixed << std::setprecision(2) << powerup[i].second;
				text = "big " + oss.str() + "\n";
				_powerupText.setString(_powerupText.getString() + text);
				//_powerupText.setString("big " + oss.str());
				_powerupText.setFillColor(paddleEffectsColour);
				break;
			case smallPaddle:
				oss << std::fixed << std::setprecision(2) << powerup[i].second;
				text = "small " + oss.str() + "\n";
				_powerupText.setString(_powerupText.getString() + text);
				//_powerupText.setString("small " + oss.str());
				_powerupText.setFillColor(paddleEffectsColour);
				break;
			case slowBall:
				oss << std::fixed << std::setprecision(2) << powerup[i].second;
				text = "slow " + oss.str() + "\n";
				_powerupText.setString(_powerupText.getString() + text);
				//_powerupText.setString("slow " + oss.str());
				_powerupText.setFillColor(ballEffectsColour);
				break;
			case fastBall:
				oss << std::fixed << std::setprecision(2) << powerup[i].second;
				text = "fast " + oss.str() + "\n";
				_powerupText.setString(_powerupText.getString() + text);
				//_powerupText.setString("fast " + oss.str());
				_powerupText.setFillColor(ballEffectsColour);
				break;
			case fireBall:
				oss << std::fixed << std::setprecision(2) << powerup[i].second;
				text = "fire " + oss.str() + "\n";
				_powerupText.setString(_powerupText.getString() + text);
				//_powerupText.setString("fire " + oss.str());
				_powerupText.setFillColor(extraBallEffectsColour);
				break;
			case none:
				//_powerupText.setString("");
		
				break;
			}

		}
		
		

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
}