#pragma once
#include "PowerupBase.h"
class PowerupStickBall : public PowerupBase
{
public:
	PowerupStickBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupStickBall();

	std::pair<POWERUPS, float> applyEffect() override;
};

