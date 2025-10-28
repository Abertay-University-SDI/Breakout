#include "PaddleSpeedEffect.h"

#include "Paddle.h"

PaddleSpeedEffect::PaddleSpeedEffect(Paddle* paddle, float paddleMoveSpeedCoeff):_paddle{paddle},_paddleMoveSpeedCoeff{paddleMoveSpeedCoeff}
{
}

void PaddleSpeedEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_paddle->setSpeed(_paddleMoveSpeedCoeff);
}

void PaddleSpeedEffect::EndEffect()
{
	_paddle->setSpeed(1.0f / _paddleMoveSpeedCoeff);
}

BaseEffect* PaddleSpeedEffect::CopyEffect()
{
	return new PaddleSpeedEffect(_paddle, _paddleMoveSpeedCoeff);
}


