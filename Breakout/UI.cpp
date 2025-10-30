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


	//_powerupBackground.setSize(sf::Vector2f(100.f, 10.f)); 
	//_powerupBackground.setFillColor(sf::Color(50, 50, 50)); 
	//_powerupBackground.setPosition(WINDOW_WIDTH - _powerupFill.getSize().x , 10.f);

	_powerupFill.setSize(sf::Vector2f(100.f, 20)); // full width initially
	_powerupFill.setFillColor(sf::Color::Green); // will be updated per powerup
	_powerupFill.setPosition(WINDOW_WIDTH + 20, 10.f);

}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	//power up bar
	float barPercentage = std::clamp(powerup.second / 5.0f, 0.f, 1.f);
	_powerupFill.setSize(sf::Vector2f(100.f * barPercentage, 20)); // shrink bar


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
		_powerupFill.setFillColor(paddleEffectsColour);

		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_powerupFill.setFillColor(ballEffectsColour);

		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		_powerupFill.setFillColor(ballEffectsColour);

		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		_powerupFill.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		_powerupFill.setSize(sf::Vector2f(0.f, 10.f)); // hide bar

		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	//_window->draw(_powerupBackground);
	_window->draw(_powerupFill);

	//_window->draw(_powerupText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}