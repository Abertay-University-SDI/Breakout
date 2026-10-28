#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
    PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem);
    ~PowerupSmallPaddle();

    //std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
};
