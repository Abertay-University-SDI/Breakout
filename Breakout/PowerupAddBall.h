#pragma once
#include "PowerupBase.h"
class PowerupAddBall : public PowerupBase
{
    
    public:
        PowerupAddBall(sf::RenderWindow * window, Paddle * paddle, Ball * ball, float x_pos);
        ~PowerupAddBall();

        std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
 
};

