#include "EffectBallSlowBall.h"


EffectBallSlowBall::EffectBallSlowBall() {};
EffectBallSlowBall::EffectBallSlowBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall) : EffectBall::EffectBall(givenMaxDuration, givenMutexEffects, givenBall) {}

void EffectBallSlowBall::applyEffect()
{
	_ball->setVelocity(0.5f, _maxDuration);
}

void EffectBallSlowBall::stopEffect()
{
	_ball->resetSpeed();
}