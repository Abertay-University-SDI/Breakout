#pragma once
#include "PowerupBase.h"

class NewPowerUp : public PowerupBase
{
public:
	NewPowerUp(sf::RenderWindow* window, Paddle* paddle, Ball* ball);

	std::pair<POWERUPS, float> applyEffect() override;

private:

};

