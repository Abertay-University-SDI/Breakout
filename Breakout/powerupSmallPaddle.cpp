#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Vector2f pos)
    : PowerupBase(window, paddle, ball, pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    _paddle->setWidth(0.67f, 5.0f);
    return { smallPaddle, 5.0f };
}