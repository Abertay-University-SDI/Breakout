#include "EffectPaddleSmallPaddle.h"


EffectPaddleSmallPaddle::EffectPaddleSmallPaddle() {}
EffectPaddleSmallPaddle::EffectPaddleSmallPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle) : EffectPaddle::EffectPaddle(givenMaxDuration, givenMutexEffects, givenPaddle) {}

void EffectPaddleSmallPaddle::applyEffect()
{
	_paddle->setWidth(0.67f, 5.0f);
}

void EffectPaddleSmallPaddle::stopEffect()
{
	_paddle->setWidth(1.f, 0.f);
}