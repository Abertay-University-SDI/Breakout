#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <queue>
#include "EffectBase.h"

/*
The effectable system handles all the effects in play at once, checking if they can be and applying them, ticking them down, and removing them when done.
It does this by use of "effectable components" that store a "tag" referring to an effect, with a time to indicate how long left.
This will resolve any issues, decode the tag, then "apply" it
*/
/*budget ecs system*/

/*Struct containing the */
struct FEffect
{
	FEffect(std::string givenEffectTag, std::vector<std::string> givenMutexEffects) 
	{
		_effectTag = givenEffectTag;
		_mutexEffects = givenMutexEffects;
		_timeRemaining = 0.f;
	}

	/*Tag that the effect manager will reference when applying and unapplying this*/
	std::string _effectTag;

	float _timeRemaining;

	/*vector of the effect tags that cannot be applied at the same time*/
	std::vector<std::string> _mutexEffects;

};


class EffectableSystem
{
public:

	EffectableSystem(class Paddle* paddle, class Ball* ball);

	~EffectableSystem();

	/*update our effects - tick down the timers, apply anything pending, remove anything old*/
	void update(float dt);

protected:

	/*unorderd map connecting the "tags" we have been dealing in up untill this point, and transferring these into actual effects*/
	std::unordered_map<std::string, std::shared_ptr<EffectBase>> _tagEffectMap;

	/*Anything else that requires other effects can go here...*/

	class Paddle* _paddle;
	class Ball* _ball;


	/*Effects that have been queued to be added next effectable system update*/
	std::queue<std::string> _effectQueue;

	/*List of our active effects - used for checking mut-ex of the effects*/
	std::unordered_map<std::string, float> _effectActiveMap;

public:

	/*Allows powerups or the gambling system to push effects this way*/
	inline void addEffectToQueue(std::string givenEffect)  { _effectQueue.push(givenEffect); }


	std::string getEffectText();
};