#include "PowerUpFastPaddle.h"

PowerupFastPaddle::PowerupFastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(fastPaddleEffectsColour); // Same colour as smallPaddle
}

PowerupFastPaddle::~PowerupFastPaddle()
{
}

std::pair<POWERUPS, float> PowerupFastPaddle::applyEffect()
{
    _paddle->setVelocity(PADDLE_POWERUP_SPEED, 5.0f);
    return { fastPaddle, 5.0f };
}