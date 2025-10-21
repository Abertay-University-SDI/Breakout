#pragma once
#include "PowerupBase.h"

class PowerupFastBall : public PowerupBase
{
public:
	PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupFastBall() override;

	std::pair<POWERUPS, sf::Vector2f> applyEffect() override;
	// Method to apply the power-up effect
};
