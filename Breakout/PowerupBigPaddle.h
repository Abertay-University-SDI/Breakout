#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
    POWERUPS checkEffect() override; // Method to apply the power-up effect

    std::pair<POWERUPS, float> applyMulti(int index) override; // Method to apply the power-up effect
    POWERUPS checkMulti(int index) override; // Method to apply the power-up effect
};
