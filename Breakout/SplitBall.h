#pragma once

#include "PowerupBase.h"

class SplitBall : public PowerupBase 
{
public:
	SplitBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
	~SplitBall();
private:
	std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
