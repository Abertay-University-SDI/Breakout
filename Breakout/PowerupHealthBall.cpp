#include "PowerupHealthBall.h"


PowerupHealthBall::PowerupHealthBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, ball, x_pos)
{
    _sprite.setFillColor(healthEffectColour);
}

PowerupHealthBall::~PowerupHealthBall()
{
}

std::pair<POWERUPS, float> PowerupHealthBall::applyEffect()
{
    _ball->gainLife();
    return { healthBall, 0.0f };
}