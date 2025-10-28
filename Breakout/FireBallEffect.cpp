#include "FireBallEffect.h"

#include "Ball.h"

FireBallEffect::FireBallEffect(Ball* ball) :_ball{ ball }
{
}

void FireBallEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_ball->addFireBall();
}

void FireBallEffect::EndEffect()
{
	_ball->subFireBall();
}

BaseEffect* FireBallEffect::CopyEffect()
{
	return new FireBallEffect(_ball);
}