#include "PowerupSlowBall.h"

PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle,
								 Ball* ball) : PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(ballEffectsColour);
}

PowerupSlowBall::~PowerupSlowBall()
{}

std::pair<POWERUPS, sf::Vector2f> PowerupSlowBall::applyEffect()
{
	_ball->setVelocity(0.5f, _maxDuration);
	return {slowBall, {_maxDuration, _maxDuration}};
}
