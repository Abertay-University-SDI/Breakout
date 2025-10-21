#pragma once

#include "PowerupBase.h"

class PowerupSlowBall : public PowerupBase
{
public:
	PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupSlowBall() override;

	std::pair<POWERUPS, sf::Vector2f> applyEffect() override;
	// Method to apply the power-up effect
};
