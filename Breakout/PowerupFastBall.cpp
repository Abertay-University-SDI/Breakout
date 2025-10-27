#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Texture* tex)
    : PowerupBase(window, paddle, ball, tex)
{

}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    _ball->setVelocity(2.f, 5.0f);
    return { fastBall, 5.0f };
}