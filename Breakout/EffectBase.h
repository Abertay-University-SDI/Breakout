#pragma once

#include <string>
#include <vector>

/*Effects are one half of the old powerups - they are the actual "thing" that happens when the powerup is picked up, or a gamble chooses it*/
/*NO LONGER ABSTRACT - One of the gambling outcomes is nothing - so this is what we  use for that...*/
class EffectBase
{
public:

	EffectBase();
	EffectBase(float givenMaxDuration, std::vector<std::string> givenMutexEffects);

	/*Apply the effect!*/
	virtual void applyEffect();

	/*Stop the effect early...*/
	virtual void stopEffect();

protected:

	float _maxDuration;

	/*List of effects that are mutually exclusive with this effect - in our case more often than not, that will be just 1, but this allows us to extend it further...*/
	std::vector<std::string> _mutexEffects;

public:

	inline float getMaxDuration() const { return _maxDuration; }

	inline std::vector <std::string> getMutexEffects() const { return _mutexEffects; }
};