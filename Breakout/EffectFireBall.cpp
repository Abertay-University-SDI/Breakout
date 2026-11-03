#include "EffectFireBall.h"
#include "GameManager.h"

EffectFireBall::EffectFireBall(GameManager* gameManager, float duration)
	: Effect(gameManager, duration)
{
}

void EffectFireBall::update(float dt)
{
	Effect::update(dt);

	if (_duration <= 0.f) { return; }

	if (auto* ball = _gameManager->getBall())
	{
		// Flickering effect
		int flicker = rand() % 50 + 205; // Random value between 205 and 255
		ball->setColour(sf::Color(flicker, flicker / 2, 0));
	}
}

void EffectFireBall::applyEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setFireBall(true);
	}
}

void EffectFireBall::endEffect()
{
	if (auto* ball = _gameManager->getBall())
	{
		ball->setFireBall(false);
		ball->setColour(sf::Color::Cyan);	// back to normal colour.
	}
}
