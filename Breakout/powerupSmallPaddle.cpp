#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    //_sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
    smallImage.loadFromFile("Images/Paddle Decreased.png");
    _sprite.setTexture(&smallImage);
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}

std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
{
    _paddle->setWidth(0.8f, 5.0f);
    return { smallPaddle, 5.0f };
}