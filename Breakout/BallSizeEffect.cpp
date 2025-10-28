#include "BallSizeEffect.h"

#include "Ball.h"

BallSizeEffect::BallSizeEffect(Ball* ball, float ballSizeMultiplier) :_ball{ ball }, _ballSizeMultiplier{ ballSizeMultiplier }
{
}

void BallSizeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_ball->setSize(_ballSizeMultiplier);
}

void BallSizeEffect::EndEffect()
{
	_ball->setSize(1.0f / _ballSizeMultiplier);
}

BaseEffect* BallSizeEffect::CopyEffect()
{
	return new BallSizeEffect(_ball, _ballSizeMultiplier);
}
