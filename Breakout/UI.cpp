#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) :
	m_window(window), m_gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;

		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);

		m_lives.push_back(newLife);
	}

	m_powerupText.setCharacterSize(30);
	m_powerupText.setPosition(800, 10);
	m_powerupText.setFillColor(sf::Color::Cyan);
	m_font.loadFromFile("font/montS.ttf");
	m_powerupText.setFont(m_font);
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
			m_powerupText.setString("big " + oss.str());
			m_powerupText.setFillColor(paddleEffectsColour);
			break;

		case smallPaddle:
			oss << std::fixed << std::setprecision(2) << powerup.second;
			m_powerupText.setString("small " + oss.str());
			m_powerupText.setFillColor(paddleEffectsColour);
			break;

		case slowBall:
			oss << std::fixed << std::setprecision(2) << powerup.second;
			m_powerupText.setString("slow " + oss.str());
			m_powerupText.setFillColor(ballEffectsColour);
			break;

		case fastBall:
			oss << std::fixed << std::setprecision(2) << powerup.second;
			m_powerupText.setString("fast " + oss.str());
			m_powerupText.setFillColor(ballEffectsColour);
			break;

		case fireBall:
			oss << std::fixed << std::setprecision(2) << powerup.second;
			m_powerupText.setString("fire " + oss.str());
			m_powerupText.setFillColor(extraBallEffectsColour);
			break;

		case none:
			m_powerupText.setString("");
		
			break;
	}
}

void UI::lifeLost(int lives)
{
	m_lives[m_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	m_window->draw(m_powerupText);

	for (sf::CircleShape life : m_lives)
	{
		m_window->draw(life);
	}
}