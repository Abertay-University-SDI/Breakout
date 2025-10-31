#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    //_sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
    bigImage.loadFromFile("Images/Paddle increased.png");
    _sprite.setTexture(&bigImage);
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
{
    _paddle->setWidth(1.5f, 5.0f);
    return { bigPaddle, 5.0f };
}