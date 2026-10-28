#pragma once
#include "PowerupBase.h"

class GameManager;

class DoublePaddle : public PowerupBase
{
public:
    DoublePaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos);
    ~DoublePaddle();

    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect
    Ball* _ball;
};

