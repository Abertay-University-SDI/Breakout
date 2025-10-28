#pragma once
#include "PowerupBase.h"
class PowerupPhantomBall : public PowerupBase
{
public:
    PowerupPhantomBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupPhantomBall();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};