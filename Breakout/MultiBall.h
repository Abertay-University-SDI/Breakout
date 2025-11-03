#pragma once
#include "PowerupBase.h"
#include "GameManager.h"
class MultiBall : public PowerupBase
{
public:
	GameManager* _gameManager;
	MultiBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
		~MultiBall();

	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

