#include "EffectSlowBall.h"
#include "GameManager.h"

EffectSlowBall::EffectSlowBall(GameManager* gameManager, float duration)
	: Effect(gameManager, duration)
{
}

void EffectSlowBall::applyEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setVelocity(0.5f);
	}
}

void EffectSlowBall::endEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setVelocity(1.0f);
	}
}
