#pragma once

#include "BaseEffect.h"

class Ball;

class BallSizeEffect : public BaseEffect
{
public:
	BallSizeEffect(Ball* ball, float ballSizeMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	BaseEffect* CopyEffect() override;

	std::string GetName() override { return "Ball size"; }
private:
	Ball* _ball;
	float _ballSizeMultiplier;
};