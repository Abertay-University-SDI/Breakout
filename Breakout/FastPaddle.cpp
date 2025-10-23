#include "FastPaddle.h"

FastPaddle::FastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball) 
	: PowerupBase(window, paddle, ball)
{
}

FastPaddle::~FastPaddle()
{
}

std::pair<POWERUPS, float> FastPaddle::applyEffect()
{
	_paddle->setSpeed(800.0f);
	return { fastPaddle, 5.0f };
}
