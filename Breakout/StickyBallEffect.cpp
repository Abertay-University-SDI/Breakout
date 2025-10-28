#include "StickyBallEffect.h"

#include "Ball.h"

StickyBallEffect::StickyBallEffect(Ball* ball) :_ball{ ball }
{
}

void StickyBallEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);

	_ball->addSticky();
}

void StickyBallEffect::EndEffect()
{
	_ball->subSticky();
}

BaseEffect* StickyBallEffect::CopyEffect()
{
	return new StickyBallEffect(_ball);
}
