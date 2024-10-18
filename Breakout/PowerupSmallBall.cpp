#include "PowerupSmallBall.h"

PowerupSmallBall::PowerupSmallBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
	: PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(CustomBallEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallBall::~PowerupSmallBall()
{
}

std::pair<POWERUPS, float> PowerupSmallBall::applyEffect()
{
	_ball->setSize(5.0, 5.0);
	return { smallBall, 5.0f };
}
