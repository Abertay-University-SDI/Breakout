#include "EffectPaddleBigPaddle.h"

EffectPaddleBigPaddle::EffectPaddleBigPaddle() {}
EffectPaddleBigPaddle::EffectPaddleBigPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle) : EffectPaddle::EffectPaddle(givenMaxDuration, givenMutexEffects, givenPaddle) {}


void EffectPaddleBigPaddle::applyEffect()
{
	_paddle->setWidth(1.5f, 5.0f);
}

void EffectPaddleBigPaddle::stopEffect()
{
	_paddle->setWidth(1.0f, 0.0f);
}