#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"

class GameManager;

class UI
{
public:
	UI(int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void setLives(int lives);
	void setNewLifeFraction(float fraction);
	void update(float dt);
	void render(sf::RenderWindow& window);

private:
	GameManager* _gameManager;
	
	sf::Font _font;
	sf::Text _powerupText;

	sf::CircleShape _lifeCircle;
	StarShape _newLifeStar;
	int _lives = INITIAL_LIVES;
	float _newLifeFraction = 0.0f;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

