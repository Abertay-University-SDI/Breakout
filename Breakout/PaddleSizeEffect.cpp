#include "PaddleSizeEffect.h"

#include "Paddle.h"

PaddleSizeEffect::PaddleSizeEffect(Paddle* paddle, float _paddleSizeMultiplier) :paddle{ paddle }, _paddleSizeMultiplier{ _paddleSizeMultiplier }
{
}

void PaddleSizeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	paddle->setWidth(_paddleSizeMultiplier);
}

void PaddleSizeEffect::EndEffect()
{
	paddle->setWidth(1 / _paddleSizeMultiplier);
}


BaseEffect* PaddleSizeEffect::CopyEffect()
{
	return new PaddleSizeEffect(paddle, _paddleSizeMultiplier);
}