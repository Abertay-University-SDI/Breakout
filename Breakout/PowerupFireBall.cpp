#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Texture* tex)
    : PowerupBase(window, paddle, ball, tex)
{

}

PowerupFireBall::~PowerupFireBall()
{
    
}

std::pair<POWERUPS, float> PowerupFireBall::applyEffect()
{
    _ball->setFireBall(5.0f);
    return { fireBall, 5.0f };
}
