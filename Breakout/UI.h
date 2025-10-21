#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();

private:
	GameManager* m_gameManager;
	
	sf::RenderWindow* m_window;
	sf::Font m_font;
	sf::Text m_powerupText;

	std::vector<sf::CircleShape> m_lives;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

