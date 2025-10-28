#include "Effects.h"

void BaseEffect::UpdateEffect(float dt)
{
	_durationLeft -= dt;

	if (_durationLeft < 0)
	{
		EndEffect();
		_shouldBeDestroyed = true;
	}
}

