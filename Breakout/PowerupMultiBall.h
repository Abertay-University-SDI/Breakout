#pragma once

#include "PowerupBase.h"

class PowerupMultiBall : public PowerupBase
{
public:
	PowerupMultiBall(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos);
	~PowerupMultiBall();

	std::tuple<POWERUPS, float, sf::Color> applyEffect() override; // Method to apply the power-up effect
};

