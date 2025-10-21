#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(Paddle* paddle, Ball* ball)
    : PowerupBase(paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
{
    _ball->setVelocity(0.5f, 5.0f);
    return { slowBall, 5.0f };
}