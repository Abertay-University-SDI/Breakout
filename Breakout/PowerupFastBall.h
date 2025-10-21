#pragma once
#include "PowerupBase.h"
class PowerupFastBall : public PowerupBase
{
public:
    PowerupFastBall(Paddle* paddle, Ball* ball);
    ~PowerupFastBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};

