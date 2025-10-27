#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
    PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Texture* tex);
    ~PowerupSmallPaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
