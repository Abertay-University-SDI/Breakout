#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "PowerupManager.h"
#include "ProgressBar.hpp"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void render();

	void updatePowerupText(std::pair<POWERUPS, sf::Vector2f>);
	void updatePowerupBar(std::pair<POWERUPS, sf::Vector2f>);

	void lifeLost(int lives);

private:
	GameManager* _gameManager;

	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;
	ProgressBar _progressBar;
	sf::CircleShape _powerupIcon{20.0f};

	std::vector<sf::CircleShape> _lives;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};
