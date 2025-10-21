#pragma once
#include "PowerupBase.h"

class PowerupFireBall : public PowerupBase
{
public:
	PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupFireBall() override;

	std::pair<POWERUPS, sf::Vector2f> applyEffect() override;
	// Method to apply the power-up effect
};
