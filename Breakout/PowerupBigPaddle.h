#pragma once

#include "PowerupBase.h"

class PowerupBigPaddle : public PowerupBase
{
public:
    PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupBigPaddle();

    std::pair<POWERUPS, float> applyEffect() override;
};
