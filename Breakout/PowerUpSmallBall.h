#pragma once
#include "PowerupBase.h"

class PowerUpSmallBall : public PowerupBase
{
public:
    PowerUpSmallBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerUpSmallBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
