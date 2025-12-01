#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
{
    _ball->changeVelocity(0.5f, 5.0f);
    return { slowBall, 5.0f };
}

POWERUPS PowerupSlowBall::checkEffect()
{
    return slowBall;
}

std::pair<POWERUPS, float> PowerupSlowBall::applyMulti(int index)
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupSlowBall::checkMulti(int index)
{
    return POWERUPS();
}
