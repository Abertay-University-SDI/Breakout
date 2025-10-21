#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle,
								 Ball* ball) : PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(ballEffectsColour);
}

PowerupFireBall::~PowerupFireBall()
{
	auto pInteger = new int();

	if (pInteger != nullptr)
	{
		// use my pointer to do things.
	}
}

std::pair<POWERUPS, sf::Vector2f> PowerupFireBall::applyEffect()
{
	_ball->setFireBall(_maxDuration);
	return {fireBall, {_maxDuration, _maxDuration}};
}
