#pragma once

#include "BaseEffect.h"

class Ball;

class FireBallEffect : public BaseEffect
{
public:
	FireBallEffect(Ball* ball);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "Fire ball"; }

	BaseEffect* CopyEffect();
private:
	Ball* _ball;
};