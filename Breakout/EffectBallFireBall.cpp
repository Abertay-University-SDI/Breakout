#include "EffectBallFireBall.h"

#include "EffectBallFastBall.h"


EffectBallFireBall::EffectBallFireBall() {}
EffectBallFireBall::EffectBallFireBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall) : EffectBall::EffectBall(givenMaxDuration, givenMutexEffects, givenBall) {}

void EffectBallFireBall::applyEffect()
{
	_ball->setFireBall(5.0f);
}

void EffectBallFireBall::stopEffect()
{

}