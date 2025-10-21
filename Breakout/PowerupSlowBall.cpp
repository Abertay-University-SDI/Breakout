#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball) :
    PowerupBase(window, paddle, ball)
{
    m_sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
{
    m_ball->setVelocity(0.5f, 5.0f);
    return { slowBall, 5.0f };
}