#include "PowerupPhantomBall.h"



PowerupPhantomBall::PowerupPhantomBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupPhantomBall::~PowerupPhantomBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }



}

std::pair<POWERUPS, float> PowerupPhantomBall::applyEffect()
{
    _ball->setPhantomBall(1.0f);
    return { phantomBall, 1.0f };
}