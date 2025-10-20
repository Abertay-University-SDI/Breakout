#pragma once
#include "PowerupManager.h"

class PowerupTimeExtender : public PowerupBase
{
public:
    PowerupTimeExtender(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupTimeExtender(){};

    std::pair<POWERUPS, float> applyEffect(float timeMult) override; // Method to apply the power-up effect
};

