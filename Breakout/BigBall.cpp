#include "BigBall.h"

BigBall::BigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball) 
	: PowerupBase(window, paddle, ball)
{
	
}

BigBall::~BigBall()
{
}

std::pair<POWERUPS, float> BigBall::applyEffect()
{
	_ball->setSize(20.f);
	return { bigBall, 5.0f };
}

