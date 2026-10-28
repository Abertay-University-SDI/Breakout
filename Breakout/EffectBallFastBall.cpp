#include "EffectBallFastBall.h"


EffectBallFastBall::EffectBallFastBall() {}
EffectBallFastBall::EffectBallFastBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall) : EffectBall::EffectBall(givenMaxDuration, givenMutexEffects, givenBall) {}

void EffectBallFastBall::applyEffect()
{
	if(_ball)
		_ball->setVelocity(2.f, _maxDuration); //Worth noting there is a duration tied into the effect on the balls end? 
}

void EffectBallFastBall::stopEffect()
{
	if(_ball)
		_ball->resetSpeed();
}