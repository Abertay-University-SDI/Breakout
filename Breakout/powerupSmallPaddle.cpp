#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem)
    : PowerupBase(window, paddle, x_pos, powerupEffect, effectableSystem)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{
}
//
//std::pair<POWERUPS, float> PowerupSmallPaddle::applyEffect()
//{
//    _paddle->setWidth(0.67f, 5.0f);
//    return { smallPaddle, 5.0f };
//}