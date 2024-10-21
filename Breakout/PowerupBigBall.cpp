#include "PowerupBigBall.h"

PowerupBigBall::PowerupBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigBall::~PowerupBigBall()
{
}

std::pair<POWERUPS, float> PowerupBigBall::applyEffect()
{
    _ball->setRadius(1.5f, 5.f);
    return { bigBall, 5.0f };
}