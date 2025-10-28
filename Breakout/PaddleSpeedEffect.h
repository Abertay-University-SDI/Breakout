#pragma once

#include "BaseEffect.h"

class Paddle;

class PaddleSpeedEffect: public BaseEffect
{
public:
	PaddleSpeedEffect(Paddle* paddle, float paddleMoveSpeedCoeff);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "Paddle Speed"; }

	BaseEffect* CopyEffect() override;
private:
	Paddle* _paddle;
	float _paddleMoveSpeedCoeff;
};

