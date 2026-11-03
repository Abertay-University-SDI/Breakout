#include "EffectFastBall.h"
#include "GameManager.h"

EffectFastBall::EffectFastBall(GameManager* gameManager, float duration)
	: Effect(gameManager, duration)
{
}

void EffectFastBall::applyEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setVelocity(2.0f);
	}
}

void EffectFastBall::endEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setVelocity(1.0f);
	}
}
