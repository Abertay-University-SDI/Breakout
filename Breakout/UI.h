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

	void updatePowerupText(std::string EffectText);

	/*Function for updating the lives text, on life lost or gained...*/
	void updateLivesText(int lives);

	/*Function just to write to the gambling text variable - as with powerups, timing handled elsewhere*/
	void updateGamblingText(std::string outcomeText);


	void render();

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;


	/*The text informing the player of how many lives they have left*/
	sf::Text _livesText;

	/*Text that sits at the bottom displaying controls and info*/
	sf::Text _controlsText;

	/*A little ball icon that goes next to our lives text*/
	sf::CircleShape _livesIcon;

	/*Text that informs you on the gambling outcomes*/
	sf::Text _gamblingText;


	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;
};

