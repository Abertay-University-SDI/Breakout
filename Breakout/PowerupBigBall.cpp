#include "PowerupBigBall.h"

PowerupBigBall::PowerupBigBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
	: PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(CustomBallEffectsColour); // Same colour as SmallPaddle
}

PowerupBigBall::~PowerupBigBall()
{
}

std::pair<POWERUPS, float> PowerupBigBall::applyEffect()
{
	_ball->setSize(20.0, 5.0);
	return { bigBall, 5.0f };
}
