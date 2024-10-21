#include "PowerupStickBall.h"

PowerupStickBall::PowerupStickBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball) 
	: PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(sf::Color::Green);
}

PowerupStickBall::~PowerupStickBall()
{
	int* pInteger = new int();

	if (pInteger != nullptr)
	{

	}
}

std::pair<POWERUPS, float> PowerupStickBall::applyEffect()
{
	_ball->setStickyBall(5.f);
	return {stickyBall, 5.0f};
}
