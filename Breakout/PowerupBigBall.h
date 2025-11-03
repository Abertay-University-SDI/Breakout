#pragma once
#include "PowerupBase.h"
class PowerupBigBall : public PowerupBase
{
public:
	PowerupBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupBigBall();

	std::pair<POWERUPS, float> applyEffect() override;
};

