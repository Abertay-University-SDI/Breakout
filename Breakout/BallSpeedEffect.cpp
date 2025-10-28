#include "BallSpeedEffect.h"

#include "Ball.h"

BallSpeedEffect::BallSpeedEffect(Ball* ball, float ballSpeedMultiplier) :ball{ ball }, ballSpeedMultiplier{ ballSpeedMultiplier }
{
}

void BallSpeedEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	ball->setVelocity(ballSpeedMultiplier);
}

void BallSpeedEffect::EndEffect()
{
	ball->setVelocity(1.0f / ballSpeedMultiplier);
}

BaseEffect* BallSpeedEffect::CopyEffect()
{
	return new BallSpeedEffect(ball, ballSpeedMultiplier);
}