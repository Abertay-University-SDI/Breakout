#pragma once
#include "EffectBase.h"
#include "Paddle.h"

/*Effect Paddles are effects that effect the paddle (see how many times I can get "effect" in a sentence?
They have a ptr to the paddle, and are also abstract
*/

class EffectPaddle : public EffectBase
{
public:

	EffectPaddle();
	EffectPaddle(float givenMaxDuration, std::vector<std::string> givenMutexEffects, Paddle* givenPaddle);

protected:

	Paddle* _paddle;

};



