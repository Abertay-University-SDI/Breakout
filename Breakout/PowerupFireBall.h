#pragma once
#include "PowerupBase.h"
class PowerupFireBall : public PowerupBase
{
public:
    PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupFireBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
    POWERUPS checkEffect() override; // Method to apply the power-up effect

    std::pair<POWERUPS, float> applyMulti(int index) override; // Method to apply the power-up effect
    POWERUPS checkMulti(int index) override; // Method to apply the power-up effect
};

