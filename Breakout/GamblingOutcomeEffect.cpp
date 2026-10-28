#include "GamblingOutcomeEffect.h"

GamblingOutcomeEffect::GamblingOutcomeEffect() : GamblingOutcomeBase::GamblingOutcomeBase() { _outcomeString = ""; }
GamblingOutcomeEffect::GamblingOutcomeEffect(int Weight, GamblingSystem* gamblingSystem, std::string givenEffect) : GamblingOutcomeBase::GamblingOutcomeBase(Weight, gamblingSystem), _effect(givenEffect) { _outcomeString = "Power up!"; }

std::string GamblingOutcomeEffect::activateOutcome()
{
	_gamblingSystem->GetGameManager()->getEffectableSystem()->addEffectToQueue(_effect);

	return _outcomeString;
}