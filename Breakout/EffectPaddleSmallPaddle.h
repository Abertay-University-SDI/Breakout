#pragma once


#include "EffectPaddle.h"

class EffectPaddleSmallPaddle : public EffectPaddle
{
public:

	EffectPaddleSmallPaddle();

	EffectPaddleSmallPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle);


	virtual void applyEffect() override;
	virtual void stopEffect() override;
};