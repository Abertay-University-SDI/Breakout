#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Paddle* paddle2, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, paddle2, ball, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    _paddle->setWidth(1.5f, 5.0f);
    _paddle2->setWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f };
}