#pragma once

#include "PowerupBase.h"

class PowerupMulti : public PowerupBase
{
public:
    PowerupMulti(sf::RenderWindow* window, Paddle* paddle, Ball* ball, std::vector<POWERUPS> powers);
    //PowerupMulti(sf::RenderWindow* window, Paddle* paddle, Ball* ball) : PowerupBase(window, paddle, ball) {}

    ~PowerupMulti();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
    POWERUPS checkEffect() override; // Method to apply the power-up effect

    std::pair<POWERUPS, float> applyMulti(int index) override; // Method to apply the power-up effect
    POWERUPS checkMulti(int index) override; // Method to apply the power-up effect

    
};
