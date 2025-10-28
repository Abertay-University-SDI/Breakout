#pragma once

#include "BaseEffect.h"

class Ball;

class BallSpeedEffect : public BaseEffect
{
public:
	BallSpeedEffect(Ball* ball, float ballSpeedMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "Ball speed"; }

	BaseEffect* CopyEffect();
private:
	Ball* ball;
	float ballSpeedMultiplier;
};