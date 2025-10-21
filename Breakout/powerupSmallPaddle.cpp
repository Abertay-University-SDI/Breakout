#include "PowerupSmallPaddle.h"

PowerupSmallPaddle::PowerupSmallPaddle(sf::RenderWindow* window, Paddle* paddle,
									   Ball* ball) : PowerupBase(
		window, paddle, ball)
{
	_sprite.setFillColor(paddleEffectsColour); // Same colour as SmallPaddle
}

PowerupSmallPaddle::~PowerupSmallPaddle()
{}

std::pair<POWERUPS, sf::Vector2f> PowerupSmallPaddle::applyEffect()
{
	_paddle->setWidth(0.67f, _maxDuration);
	return {smallPaddle, {_maxDuration, _maxDuration}};
}
