#pragma once
#include "PowerupBase.h"
class PowerupFireBall : public PowerupBase
{
public:
    PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Texture* tex);
    ~PowerupFireBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect

};

