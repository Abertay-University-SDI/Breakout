#pragma once
#include "PowerupBase.h"
class PowerupFireBall : public PowerupBase
{
public:
    PowerupFireBall(Paddle* paddle, Ball* ball);
    ~PowerupFireBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

