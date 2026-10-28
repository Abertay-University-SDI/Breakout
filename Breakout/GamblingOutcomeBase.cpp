#include "GamblingOutcomeBase.h"


GamblingOutcomeBase::GamblingOutcomeBase()
{
}

GamblingOutcomeBase::GamblingOutcomeBase(int Weight, GamblingSystem* gamblingSystem) : _gamblingSystem(gamblingSystem), _weight(Weight)
{
	_outcomeString = "Nothing happens. Womp Womp.";
}

std::string GamblingOutcomeBase::activateOutcome()
{

	return _outcomeString;
}