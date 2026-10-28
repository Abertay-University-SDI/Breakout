#pragma once

#include "GamblingOutcomeBase.h"


/*
* Gambling outcome effects are the broad range of gambling outcomes that add an "effects" tag to our effects system
*/

class GamblingOutcomeEffect : public GamblingOutcomeBase
{
public:

	GamblingOutcomeEffect();
	GamblingOutcomeEffect(int Weight, GamblingSystem* gamblingSystem, std::string givenEffect);


	std::string _effect;

	/*Override to add the tag...*/
	virtual std::string activateOutcome();
};