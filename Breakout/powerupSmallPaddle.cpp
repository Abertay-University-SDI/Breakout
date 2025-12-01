#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    _paddle->changeWidth(0.67f, 5.0f);
    return { smallPaddle, 5.0f };
}

POWERUPS PowerupSmallPaddle::checkEffect()
{
    return smallPaddle;
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyMulti(int index)
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupSmallPaddle::checkMulti(int index)
{
    return POWERUPS();
}
