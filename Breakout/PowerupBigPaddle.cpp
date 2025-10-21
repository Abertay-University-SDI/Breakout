#include "PowerupBigPaddle.h"

PowerupBigPaddle::PowerupBigPaddle(sf::RenderWindow* window, Paddle* paddle,
								   Ball* ball) : PowerupBase(
		window, paddle, ball)
{
	_sprite.setFillColor(paddleEffectsColour); // Same colour as smallPaddle
}

PowerupBigPaddle::~PowerupBigPaddle()
{}

std::pair<POWERUPS, sf::Vector2f> PowerupBigPaddle::applyEffect()
{
	_paddle->setWidth(1.5f, _maxDuration);
	return {bigPaddle, {_maxDuration, _maxDuration}};
}
