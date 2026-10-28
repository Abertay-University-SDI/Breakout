#pragma once
#include "PowerupBase.h"
class PowerupHealthBall : public PowerupBase
{
public:
    PowerupHealthBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
    ~PowerupHealthBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

