#include "PowerupLargeBall.h"

PowerupLargeBall::PowerupLargeBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupLargeBall::~PowerupLargeBall()
{
    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }
}

std::pair<POWERUPS, float> PowerupLargeBall::applyEffect()
{
    _ball->setSize(2.0f, 5.0f);
    return { largeBall, 5.0f };
}