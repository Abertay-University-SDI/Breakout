#include "PowerupInfectedBall.h"



PowerupInfectedBall::PowerupInfectedBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupInfectedBall::~PowerupInfectedBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }



}

std::pair<POWERUPS, float> PowerupInfectedBall::applyEffect()
{
    _ball->setInfBall(5.0f);
    return { infectedBall, 5.0f };
}