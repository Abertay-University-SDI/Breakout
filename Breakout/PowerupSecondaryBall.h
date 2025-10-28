#pragma once

#include "PowerupBase.h"

class PowerupSecondaryBall : public PowerupBase
{
public:
    PowerupSecondaryBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Vector2f pos);
    ~PowerupSecondaryBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
