#pragma once
#include "Effect.h"

class EffectSmallPaddle : public Effect
{
public:
	EffectSmallPaddle(GameManager* gameManager, float duration);

	virtual void applyEffect() override;
	virtual void endEffect() override;

};

