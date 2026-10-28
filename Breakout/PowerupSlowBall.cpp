#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Paddle* paddle2, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, paddle2, ball, x_pos)
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