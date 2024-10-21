#pragma once
#include "PowerupBase.h"

class PowerUpBigBall : public PowerupBase
{

public:
    PowerUpBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerUpBigBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

