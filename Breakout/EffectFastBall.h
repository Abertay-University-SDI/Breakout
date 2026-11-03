#pragma once
#include "Effect.h"

class EffectFastBall : public Effect
{
public:
	EffectFastBall(GameManager* gameManager, float duration);

	virtual void applyEffect() override;
	virtual void endEffect() override;

};

