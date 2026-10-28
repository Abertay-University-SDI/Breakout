#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Paddle* paddle2, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, paddle2, ball, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFireBall::~PowerupFireBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }


    
}

std::pair<POWERUPS, float> PowerupFireBall::applyEffect()
{
    _ball->setFireBall(5.0f);
    return { fireBall, 5.0f };
}