#include "PowerupTimeExtender.h"

PowerupTimeExtender::PowerupTimeExtender(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
	: PowerupBase(window, paddle, ball)
{
	_sprite.setFillColor(timeExtendEffectsColour);
}

std::pair<POWERUPS, float> PowerupTimeExtender::applyEffect(float timeMult)
{
	return { timeExtend, 1.5f };
}
