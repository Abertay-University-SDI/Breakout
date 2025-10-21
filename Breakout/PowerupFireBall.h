#pragma once
#include "PowerupBase.h"
class PowerupFireBall : public PowerupBase
{
public:
    PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupFireBall();

    std::pair<POWERUPS, float> applyEffect() override;

};

