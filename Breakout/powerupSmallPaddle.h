#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
	PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupSmallPaddle() override;

	std::pair<POWERUPS, sf::Vector2f> applyEffect() override;
	// Method to apply the power-up effect
};
