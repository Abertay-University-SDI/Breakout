#include "PowerupAddBall.h"

PowerupAddBall::PowerupAddBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos) : PowerupBase(window, paddle, ball, x_pos)
{
	_sprite.setFillColor(sf::Color::Green);
}

PowerupAddBall::~PowerupAddBall()
{
}

std::pair<POWERUPS, float> PowerupAddBall::applyEffect()
{
	return { POWERUPS::addBall, 0.f };
}
