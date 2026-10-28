#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem)
    : PowerupBase(window, paddle, x_pos, powerupEffect, effectableSystem)
{
    _sprite.setFillColor(ballEffectsColour); 
}

PowerupSlowBall::~PowerupSlowBall()
{
}

//std::pair<POWERUPS, float> PowerupSlowBall::applyEffect()
//{
//    _ball->setVelocity(0.5f, 5.0f);
//    return { slowBall, 5.0f };
//}