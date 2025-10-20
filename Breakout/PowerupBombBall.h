#pragma once
#include "PowerupBase.h"
class PowerupBombBall : public PowerupBase
{
public:
    PowerupBombBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupBombBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

