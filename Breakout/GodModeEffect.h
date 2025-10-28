#pragma once

#include "BaseEffect.h"

class Ball;

class GodModeEffect: public BaseEffect
{
public:
	GodModeEffect(Ball* ball);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	std::string GetName() override { return "God Mode"; }
	BaseEffect* CopyEffect() override;
private:
	Ball* _ball;
};