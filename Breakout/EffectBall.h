#pragma once

#include "EffectBase.h"
#include "Ball.h"

/*As with Effect Paddle, these effects are another abstract class for effects that effect the ball to derrive from*/
class EffectBall : public EffectBase
{
public:


	EffectBall();

	EffectBall(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Ball* givenBall);

protected:

	Ball* _ball;
};