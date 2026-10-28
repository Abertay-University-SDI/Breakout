#include "PowerupFastBall.h"




PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos, std::string powerupEffect, EffectableSystem* effectableSystem)
    : PowerupBase::PowerupBase(window, paddle, x_pos, powerupEffect, effectableSystem)
{
    _sprite.setFillColor(ballEffectsColour);
}
PowerupFastBall::~PowerupFastBall()
{ }