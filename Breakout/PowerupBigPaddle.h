#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
	PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupBigPaddle() override;

	std::pair<POWERUPS, sf::Vector2f> applyEffect() override;
	// Method to apply the power-up effect
};
