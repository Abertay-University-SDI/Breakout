#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    _ball->changeVelocity(2.f, 5.0f);
    return { fastBall, 5.0f };
}

POWERUPS PowerupFastBall::checkEffect()
{
    return fastBall;
}

std::pair<POWERUPS, float> PowerupFastBall::applyMulti(int index)
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupFastBall::checkMulti(int index)
{
    return POWERUPS();
}
