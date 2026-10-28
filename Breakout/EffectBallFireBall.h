#pragma once

#include "EffectBall.h"


class EffectBallFireBall : public EffectBall
{
public:

	EffectBallFireBall();
	EffectBallFireBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall);


	virtual void applyEffect() override;
	virtual void stopEffect() override;

};