#include "EffectBall.h"


EffectBall::EffectBall() : EffectBase::EffectBase(), _ball(nullptr) {}

EffectBall::EffectBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall) : EffectBase::EffectBase(givenMaxDuration, givenMutexEffects), _ball(givenBall) {}