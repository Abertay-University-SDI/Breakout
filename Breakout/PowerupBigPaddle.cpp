#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    _paddle->changeWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f };
}

POWERUPS PowerupBigPaddle::checkEffect() {
    return bigPaddle;
}

std::pair<POWERUPS, float> PowerupBigPaddle::applyMulti(int index)
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupBigPaddle::checkMulti(int index)
{
    return POWERUPS();
}
