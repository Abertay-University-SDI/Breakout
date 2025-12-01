#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
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

POWERUPS PowerupFireBall::checkEffect()
{
    return fireBall;
}

std::pair<POWERUPS, float> PowerupFireBall::applyMulti(int index)
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupFireBall::checkMulti(int index)
{
    return POWERUPS();
}
