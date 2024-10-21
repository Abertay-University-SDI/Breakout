#include "PowerUpBigBall.h"

PowerUpBigBall::PowerUpBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(sf::Color::Magenta);
}

PowerUpBigBall::~PowerUpBigBall()
{
}

std::pair<POWERUPS, float> PowerUpBigBall::applyEffect()
{
    _ball->setBigball(5.f);
    return { bigBall, 5.0f };
}