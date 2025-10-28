#include "DebugEffect.h"

#include <iostream>

DebugEffect::DebugEffect(const std::string& _debugMessage) :_debugMessage{ _debugMessage }
{
}

void DebugEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	std::cout << _debugMessage << '\n';
}



BaseEffect* DebugEffect::CopyEffect()
{
	return new DebugEffect(_debugMessage);
}