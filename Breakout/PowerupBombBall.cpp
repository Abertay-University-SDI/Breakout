#include "PowerupBombBall.h"


PowerupBombBall::PowerupBombBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupBombBall::~PowerupBombBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }
}

std::pair<POWERUPS, float> PowerupBombBall::applyEffect()
{
    _ball->setPowerup(5.0f, POWERUPS::bombBall);
    return { bombBall, 5.0f };
}