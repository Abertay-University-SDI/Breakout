#include "EffectBase.h"


EffectBase::EffectBase() : _maxDuration(0.f), _mutexEffects({}) {}

EffectBase::EffectBase(float givenMaxDuration, std::vector<std::string> givenMutexEffects) : _maxDuration(givenMaxDuration), _mutexEffects(givenMutexEffects) {}

void EffectBase::applyEffect() {}

void EffectBase::stopEffect() {}