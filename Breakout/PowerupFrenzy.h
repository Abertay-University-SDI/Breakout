#pragma once
#include "PowerupBase.h"
class PowerupFrenzy : public PowerupBase
{
public:
    PowerupFrenzy(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupFrenzy();

    std::pair<POWERUPS, float> applyEffect() override; 

};

