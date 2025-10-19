#pragma once
#include "PowerupBase.h"
class PowerupLargeBall : public PowerupBase
{
public:
	PowerupLargeBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupLargeBall();

	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

