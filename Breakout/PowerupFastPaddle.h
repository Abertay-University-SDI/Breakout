#pragma once
#include "PowerupBase.h"
class PowerupFastPaddle : public PowerupBase
{
public:
	PowerupFastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupFastPaddle();

	std::pair<POWERUPS, float> applyEffect() override;
};

