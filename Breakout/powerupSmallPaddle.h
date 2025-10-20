#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
    PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupSmallPaddle();

    std::pair<POWERUPS, float> applyEffect(float timeMult) override; // Method to apply the power-up effect
};
