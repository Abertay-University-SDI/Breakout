#include "DoublePaddle.h"
#include "GameManager.h"

DoublePaddle::DoublePaddle(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos) : PowerupBase(window, paddle, ball, x_pos), _ball(ball)
{
	_sprite.setFillColor(paddleEffectsColour);
}

DoublePaddle::~DoublePaddle()
{
	//_ball->getGameManager()->DoubleP = false;
}

std::pair<POWERUPS, float> DoublePaddle::applyEffect()
{
	_ball->getGameManager()->DoubleP = true;
	return {doublePaddle,5.0f };
}