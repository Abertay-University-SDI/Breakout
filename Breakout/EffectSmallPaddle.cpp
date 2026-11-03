#include "EffectSmallPaddle.h"
#include "GameManager.h"

EffectSmallPaddle::EffectSmallPaddle(GameManager* gameManager, float duration)
	: Effect(gameManager, duration)
{
}

void EffectSmallPaddle::applyEffect()
{
	if (auto* paddle = _gameManager->getPaddle())
	{
		paddle->setWidth(0.67f);
	}
}

void EffectSmallPaddle::endEffect()
{
	if (auto* paddle = _gameManager->getPaddle())
	{
		paddle->setWidth(1.0f);
	}
}