#pragma once
#include "Effect.h"

class EffectSlowBall : public Effect
{
public:
	EffectSlowBall(GameManager* gameManager, float duration);

	virtual void applyEffect() override;
	virtual void endEffect() override;

};

