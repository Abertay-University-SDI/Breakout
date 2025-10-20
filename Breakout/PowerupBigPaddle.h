#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect(float timeMult) override; // Method to apply the power-up effect
};
