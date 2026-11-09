#pragma once
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "PowerupManager.h"

//Pause Menu Enum 
enum class PauseOptions { RESUME, RESTART, EXIT };

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);
	void render();

	//Pause Menu functions
	int getPauseAt(sf::Vector2f pos) const;
	void updatePauseOption(int delta);
	void resetPauseMenu();			
	void renderPauseMenu();			
	void setPauseOption(int option);
	PauseOptions getPauseOption() const;

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;

	std::vector<sf::CircleShape> _lives;

	//Powerup bar
	sf::RectangleShape _powerupBar;
	sf::RectangleShape _powerupBarBackground;
	float _powerupBarMaxTime = 0.f;
	POWERUPS _lastPowerup = none;

	//Pause Menu variables
	sf::RectangleShape _pauseScreen;
	sf::RectangleShape _pauseMenu;
	sf::Text _pauseText;
	std::vector<sf::RectangleShape> _pauseOptions;
	std::vector<sf::Text> _pauseLabels;
	int _selectedOption = 0;


	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

