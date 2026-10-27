#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>
#include<iostream>

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

	progressBar = new sf::RectangleShape;
	progressBar->setFillColor(sf::Color::Magenta);
	progressBar->setOutlineColor(sf::Color::Black);
	progressBar->setOutlineThickness(1.0f);
	progressBar->setSize({1000,5});
	progressBar->setPosition({0,0});


	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	std::cout << window->getSize().x;
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

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
	
}

void UI::blockBroke(int remainingBricks) {

	
	progressBar->setSize(sf::Vector2f(20*remainingBricks,5));
	//progressBar->setFillColor(sf::Color::Green);

}

void UI::render()
{
	
	_window->draw(_powerupText);

	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}

	_window->draw(*progressBar);
}