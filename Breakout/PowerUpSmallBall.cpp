#include "PowerUpSmallBall.h"

PowerUpSmallBall::PowerUpSmallBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(sf::Color::Magenta); 
}

PowerUpSmallBall::~PowerUpSmallBall()
{
}

std::pair<POWERUPS, float> PowerUpSmallBall::applyEffect()
{
    _ball->setSmallball(5.f);
    return { smallBall, 5.0f };
}