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

	_powerupIcon.setFillColor(sf::Color::White);
	_powerupIcon.setOutlineThickness(0.0f);
	_powerupIcon.setRadius(LIFE_RADIUS);
	_powerupIcon.setPosition(800, 10);
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

void UI::updatePowerupIcon(const std::pair<POWERUPS, float> powerup)
{
	// Change the colour of the powerup icon based on the type of powerup.
	switch (powerup.first)
	{
	case bigPaddle:
		_powerupIcon.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		_powerupIcon.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		_powerupIcon.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		_powerupIcon.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		_powerupIcon.setFillColor(ballEffectsColour);
		break;
	case none:
		_powerupIcon.setFillColor(sf::Color::Transparent);
	}

	// Icon should flash in opacity when the duration of the powerup is nearly over.
	if (powerup.second > FLASHING_DURATION)
	{
		return;
	}

	float inter_a;	// Value of 0 = fully invisible. Value of 1 = fully visible.
	float inter_t = FLASHING_DURATION - powerup.second;

	inter_a = abs(std::sin(inter_t * PI * NUMBER_OF_FLASHES / FLASHING_DURATION));
	inter_a = std::clamp(inter_a, 0.0f, 1.0f);

	float opacity = 255 * inter_a;	// Alpha value in SFML between 0 and 255.

	auto colour = _powerupIcon.getFillColor();
	colour.a = opacity;

	_powerupIcon.setFillColor(colour);	// Set newly calculated opacity value.
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	/*_window->draw(_powerupText);*/
	_window->draw(_powerupIcon);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}