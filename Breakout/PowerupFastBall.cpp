#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    //_sprite.setFillColor(ballEffectsColour);
    fastImage.loadFromFile("Images/Speed.png");
    _sprite.setTexture(&fastImage);
}

PowerupFastBall::~PowerupFastBall()
{
}

std::pair<POWERUPS, float> PowerupFastBall::applyEffect()
{
    _ball->setVelocity(1.5f, 5.0f);
    _paddle->setVel(2.f, 5.0f);
    return { fastBall, 5.0f };
}