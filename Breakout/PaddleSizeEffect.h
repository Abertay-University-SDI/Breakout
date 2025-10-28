#pragma once

#include "BaseEffect.h"

class Paddle;

class PaddleSizeEffect : public BaseEffect
{
public:
	PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier = 1.0f);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "Paddle size"; }

	BaseEffect* CopyEffect();
private:
	Paddle* paddle;
	float _paddleSizeMultiplier;
};