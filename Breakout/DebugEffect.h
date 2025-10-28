#pragma once

#include "BaseEffect.h"

class DebugEffect : public BaseEffect
{
public:
	DebugEffect(const std::string& _debugMessage = "Hello, World!");
	std::string _debugMessage;

	void ApplyEffect(float duration) override;
	void EndEffect() override {}

	std::string GetName() override { return "Debug"; }

	BaseEffect* CopyEffect();
};