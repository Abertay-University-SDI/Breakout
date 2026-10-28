#pragma once

#include "EffectBall.h"

class EffectBallFastBall : public EffectBall
{
public:

	EffectBallFastBall();
	EffectBallFastBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall);


	virtual void applyEffect() override;
	virtual void stopEffect() override;
};
