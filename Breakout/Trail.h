#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class GameManager;

class Trail
{
public:
	Trail(sf::RenderWindow* window, GameManager* gameManager);
	~Trail();

	void CreateTrail(sf::Vector2f ballPosition); 

	void render(float dt);

private:
	GameManager* _gameManager;
	sf::RenderWindow* _window;

	static const int SIZE_OF_TRAIL = 10;

	std::vector<sf::RectangleShape> trailVector;
	sf::Texture trailTexture;
};