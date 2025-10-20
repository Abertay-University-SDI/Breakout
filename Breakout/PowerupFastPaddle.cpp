#include "PowerupFastPaddle.h"

PowerupFastPaddle::PowerupFastPaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball) : PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(paddleEffectsColour);
}

PowerupFastPaddle::~PowerupFastPaddle()
{
}

std::pair<POWERUPS, float> PowerupFastPaddle::applyEffect()
{
	_paddle->setSpeed(600, 5.0f);
	return { fastPaddle, 5.0f };
}
