#pragma once
#include "PowerupBase.h"
class PowerupInfectedBall : public PowerupBase
{
public:
    PowerupInfectedBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupInfectedBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};