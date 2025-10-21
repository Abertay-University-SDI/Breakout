#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle,
								 Ball* ball) : PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(ballEffectsColour);
}

PowerupFastBall::~PowerupFastBall()
{}

std::pair<POWERUPS, sf::Vector2f> PowerupFastBall::applyEffect()
{
	_ball->setVelocity(2.f, _maxDuration);
	return {fastBall, {_maxDuration, _maxDuration}};
}
