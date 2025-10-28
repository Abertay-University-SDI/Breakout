#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Vector2f pos);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
