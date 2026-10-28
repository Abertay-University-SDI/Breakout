#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Paddle* paddle2, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, paddle2, ball, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    _ball->setVelocity(2.f, 5.0f);
    return { fastBall, 5.0f };
}