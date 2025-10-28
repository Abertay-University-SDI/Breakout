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

	void updatePowerupText(const std::vector<std::shared_ptr<BaseEffect>> effects);
	void lifeLost(int lives);
	void render();

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;

	std::vector<sf::CircleShape> _lives;

	const sf::Color lifeColor = sf::Color::Red;
	const sf::Color lostLifeColor = sf::Color::Transparent;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

