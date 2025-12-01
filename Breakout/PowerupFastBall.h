#pragma once
#include "PowerupBase.h"
class PowerupFastBall : public PowerupBase
{
public:
    PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupFastBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
    POWERUPS checkEffect() override; // Method to apply the power-up effect

    std::pair<POWERUPS, float> applyMulti(int index) override; // Method to apply the power-up effect
    POWERUPS checkMulti(int index) override; // Method to apply the power-up effect

};

