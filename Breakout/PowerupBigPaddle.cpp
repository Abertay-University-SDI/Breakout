#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball) :
    PowerupBase(window, paddle, ball)
{
    m_sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    m_paddle->setWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f };
}