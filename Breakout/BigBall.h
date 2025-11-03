#pragma once
#include "PowerupBase.h"
class BigBall : public PowerupBase
{
public :
	BigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~BigBall();

	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};

