#include "EffectPaddle.h"
#include "Paddle.h"


EffectPaddle::EffectPaddle() : _paddle(nullptr) {}
EffectPaddle::EffectPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle) : EffectBase::EffectBase(givenMaxDuration, givenMutexEffects), _paddle(givenPaddle) {}