#include "GamblingOutcomeAddBall.h"
#include "GamblingSystem.h"

GamblingOutcomeAddBall::GamblingOutcomeAddBall(){}


GamblingOutcomeAddBall::GamblingOutcomeAddBall(int Weight, GamblingSystem* gamblingSystem, int balls) : GamblingOutcomeBase(Weight, gamblingSystem), _balls(balls)
{
	_outcomeString = "You got some balls";
}

std::string GamblingOutcomeAddBall::activateOutcome()
{
	if (_gamblingSystem)
	{
		_gamblingSystem->GetGameManager()->addLives(_balls);
	}

	return GamblingOutcomeBase::activateOutcome();
}