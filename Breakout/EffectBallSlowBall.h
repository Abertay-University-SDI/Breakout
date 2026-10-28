#pragma once


#include "EffectBall.h"

class EffectBallSlowBall : public EffectBall
{
public:

	EffectBallSlowBall();
	EffectBallSlowBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall);


	virtual void applyEffect() override;
	virtual void stopEffect() override;
};