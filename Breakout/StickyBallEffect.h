#pragma once

#include "BaseEffect.h"

class Ball;

class StickyBallEffect : public BaseEffect
{
public:
	StickyBallEffect(Ball* ball);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "Sticky Ball"; }
	BaseEffect* CopyEffect() override;
private:
	Ball* _ball;
};