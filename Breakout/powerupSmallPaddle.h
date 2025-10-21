#pragma once

#include "PowerupBase.h"

class PowerupSmallPaddle : public PowerupBase
{
public:
    PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupSmallPaddle();

    std::pair<POWERUPS, float> applyEffect() override;
};
