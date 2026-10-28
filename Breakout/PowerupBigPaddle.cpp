#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem)
    : PowerupBase(window, paddle, x_pos, powerupEffect, effectableSystem)
{
    _sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{
}

//std::pair<POWERUPS,float> PowerupBigPaddle::applyEffect()
//{
//    _paddle->setWidth(1.5f, 5.0f);
//    return { bigPaddle, 5.0f };
//}