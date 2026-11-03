#include "EffectManager.h"
#include "GameManager.h"

EffectManager::EffectManager(sf::RenderWindow* window, GameManager* gameManager)
	: _window(window), _gameManager(gameManager)
{
}

void EffectManager::update(float dt)
{
	for (auto it = _activeEffects.begin(); it != _activeEffects.end();)
	{
		if ((*it)->getDuration() <= 0.f)
		{
			/* Get the index we are currently at so we can remove it from the pair list. */
			size_t index = std::distance(_activeEffects.begin(), it);
			_activePowerups.erase(std::next(_activePowerups.begin(), index));

			/* _activeEffects elements are unique_ptrs so (hopefully) they delete themselves when removed from the list. */
			it = _activeEffects.erase(it);
		}
		else
		{
			(*it)->update(dt);
			++it;
		}
	}

	/* Make sure POWERUPS/duration list is up to date. */
	for (size_t i = 0; i < _activePowerups.size(); ++i)
	{
		_activePowerups[i].second = _activeEffects[i]->getDuration();
	}
}

void EffectManager::addEffect(std::pair<POWERUPS, float> givenPowerup)
{
	if (givenPowerup.first == none) { return; }

	/* Check if powerup is already in effect. */
	auto it = findActivePowerup(givenPowerup.first);
	if (it != _activePowerups.end())
	{
		/* Update powerup/effect to new duration */
		(*it).second = givenPowerup.second;

		size_t index = std::distance(_activePowerups.begin(), it);
		_activeEffects.at(index)->setDuration(givenPowerup.second);
		/* Maybe call the applyEffect again. Won't do that yet incase it breaks everything. */

		return;
	}

	/* Create new unique_ptr for the given powerup and add it to the effects list. */

	switch (givenPowerup.first)
	{
	case bigPaddle:
		_activeEffects.push_back(std::make_unique<EffectBigPaddle>(_gameManager, givenPowerup.second));
		break;
	case smallPaddle:
		_activeEffects.push_back(std::make_unique<EffectSmallPaddle>(_gameManager, givenPowerup.second));
		break;
	case fastBall:
		_activeEffects.push_back(std::make_unique<EffectFastBall>(_gameManager, givenPowerup.second));
		break;
	case slowBall:
		_activeEffects.push_back(std::make_unique<EffectSlowBall>(_gameManager, givenPowerup.second));
		break;
	case fireBall:
		_activeEffects.push_back(std::make_unique<EffectFireBall>(_gameManager, givenPowerup.second));
		break;
	}

	/* Make sure to apply the newly added effect. */
	_activeEffects[_activeEffects.size() - 1]->applyEffect();

	_activePowerups.push_back(givenPowerup);
}



std::vector<std::pair<POWERUPS, float>> EffectManager::getActivePowerups() const { return _activePowerups; }

std::pair<POWERUPS, float> EffectManager::getFirstActivePowerup()
{
	if (_activePowerups.size() == 0) { return std::pair<POWERUPS, float>(none, 0.0f); }
	
	return _activePowerups[0];
}

std::vector<std::pair<POWERUPS, float>>::iterator EffectManager::findActivePowerup(POWERUPS powerup)
{
	// Custom find function based of the POWERUPS value of the pair.

	auto it = std::vector<std::pair<POWERUPS, float>>::iterator();

	for (it = _activePowerups.begin(); it != _activePowerups.end(); ++it)
	{
		if ((*it).first == powerup) { return it; }
	}

	return it;	// it = _activePowerups.end()
}
