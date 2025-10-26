#include "NewPowerUp.h"

NewPowerUp::NewPowerUp(sf::RenderWindow* window, Paddle* paddle, Ball* ball) : PowerupBase(window, paddle, ball)
{
}

std::pair<POWERUPS, float> NewPowerUp::applyEffect()
{
    _ball->setNewBall();
    return { newEffect, 6.0f };
}
