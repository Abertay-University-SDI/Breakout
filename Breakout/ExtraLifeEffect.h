#pragma once

#include "BaseEffect.h"

class LivesCounter;

class ExtraLifeEffect : public BaseEffect
{
public:
	ExtraLifeEffect(LivesCounter* livesCounter);

	void ApplyEffect(float duration) override;
	void EndEffect() override;

	BaseEffect* CopyEffect() override;
	std::string GetName() override;
private:
	LivesCounter* _livesCounter;
};