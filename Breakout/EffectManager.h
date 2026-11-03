#pragma once

/* The different type of Effects */
#include "Effect.h"	// EffectBase
#include "EffectBigPaddle.h"
#include "EffectFastBall.h"
#include "EffectFireBall.h"
#include "EffectSlowBall.h"
#include "EffectSmallPaddle.h"

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

#include <vector>
#include <memory>
#include <random>

class EffectManager
{
public:
	EffectManager(sf::RenderWindow* window, GameManager* gameManager);

	void update(float dt);
	void addEffect(std::pair<POWERUPS, float> givenPowerup);

	std::vector<std::pair<POWERUPS, float>> getActivePowerups() const;
	std::pair<POWERUPS, float> getFirstActivePowerup();	// Using this for now so it doesn't break.
private:
	std::vector<std::pair<POWERUPS, float>>::iterator findActivePowerup(POWERUPS powerup);

	sf::RenderWindow* _window;
	GameManager* _gameManager;

	std::vector<std::unique_ptr<Effect>> _activeEffects;		// Used for updating the currently active effects.
	std::vector<std::pair<POWERUPS, float>> _activePowerups;	// Used for storing which powerups are active at a given time and for how long.
};

