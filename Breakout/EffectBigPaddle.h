#pragma once
#include "Effect.h"

class EffectBigPaddle : public Effect
{
public:
	EffectBigPaddle(GameManager* gameManager, float duration);

	virtual void applyEffect() override;
	virtual void endEffect() override;
};

