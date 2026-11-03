#include "Effect.h"
#include "GameManager.h"

Effect::Effect(GameManager* gameManager, float duration)
	: _gameManager(gameManager), _duration(duration)
{
	//applyEffect();
}

void Effect::update(float dt)
{
	_duration -= dt;

	if (_duration <= 0)
	{
		endEffect();
	}
}

void Effect::setDuration(float duration)
{
	_duration = duration;
}

float Effect::getDuration() const { return _duration; }
