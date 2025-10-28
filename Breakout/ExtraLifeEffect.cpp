#include "ExtraLifeEffect.h"

#include "LivesCounter.h"

ExtraLifeEffect::ExtraLifeEffect(LivesCounter* livesCounter): _livesCounter{livesCounter}
{
}

void ExtraLifeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_livesCounter->AddLife();
}

void ExtraLifeEffect::EndEffect()
{
}

BaseEffect* ExtraLifeEffect::CopyEffect()
{
	return new ExtraLifeEffect(_livesCounter);
}

std::string ExtraLifeEffect::GetName()
{
	return "Extra life";
}
