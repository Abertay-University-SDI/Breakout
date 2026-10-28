#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Paddle* paddle2, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, paddle2, ball, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    _paddle->setWidth(0.67f, 5.0f);
    _paddle2->setWidth(0.67f, 5.0f);
    return { smallPaddle, 5.0f };
}