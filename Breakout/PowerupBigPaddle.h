#pragma once

#include "PowerupManager.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem);
    ~PowerupBigPaddle();

    //std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
