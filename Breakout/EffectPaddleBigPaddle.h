#pragma once

#include "EffectPaddle.h"


class EffectPaddleBigPaddle : public EffectPaddle
{
public:

	EffectPaddleBigPaddle();

	EffectPaddleBigPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle);


	virtual void applyEffect() override;
	virtual void stopEffect() override;

};