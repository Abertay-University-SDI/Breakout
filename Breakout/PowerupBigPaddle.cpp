#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos)
    : PowerupBase(window, paddle, balls, x_pos)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
    _colour = paddleEffectsColour;
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::tuple<POWERUPS, float, sf::Color> PowerupBigPaddle::applyEffect()
{
    _paddle->setWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f , _colour };
}