#pragma once
#include "PowerupBase.h"
class FastPaddle : public PowerupBase
{
public:
	FastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~FastPaddle();

	std::pair<POWERUPS, float> applyEffect() override;
};

