#pragma once
#include "Effect.h"

class EffectFireBall : public Effect
{
public:
	EffectFireBall(GameManager* gameManager, float duration);

	virtual void update(float dt) override;
	virtual void applyEffect() override;
	virtual void endEffect() override;
};

