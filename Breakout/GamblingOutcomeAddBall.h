#pragma once
#include "GamblingOutcomeBase.h"

/*Gambling outcome simply adding 1 ball to the lives counter*/
class  GamblingOutcomeAddBall : public GamblingOutcomeBase
{

public:

	GamblingOutcomeAddBall();

	GamblingOutcomeAddBall(int Weight, GamblingSystem* gamblingSystem, int balls);

	virtual std::string activateOutcome() override;

private:

	int _balls;
};