#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball) :
    PowerupBase(window, paddle, ball)
{
    m_sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    m_ball->setVelocity(2.f, 5.0f);
    return { fastBall, 5.0f };
}