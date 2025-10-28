#include "GodModeEffect.h"

#include "Ball.h"

GodModeEffect::GodModeEffect(Ball* ball):_ball{ball}
{
}

void GodModeEffect::ApplyEffect(float duration)
{
	BaseEffect::ApplyEffect(duration);
	_ball->addGodmode();
}

void GodModeEffect::EndEffect()
{
	_ball->subGodmode();
}

BaseEffect* GodModeEffect::CopyEffect()
{
	return new GodModeEffect(_ball);
}
