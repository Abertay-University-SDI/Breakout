#pragma once
#include "PowerupBase.h"
class PowerupFastBall : public PowerupBase
{
public:
    PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupFastBall();

    std::pair<POWERUPS, float> applyEffect(float timeMult) override; // Method to apply the power-up effect


};

