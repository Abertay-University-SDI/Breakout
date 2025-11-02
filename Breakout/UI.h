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

	void powerUpBarInit();
	void powerUpBarUpdate();
	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();
	
private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;

	std::vector<sf::CircleShape> _lives;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;

	// power up progress bar
	bool _showBar = false;
	sf::RectangleShape _powerupBarBG;
	sf::RectangleShape _powerupBar;
	sf::Clock _clock;

	float bgX = 200.f;
	float bgY = 40.f;

	float barX = 190.f;
	float barY = 30.f;
	
};

