#include "EffectableSystem.h"
#include "Paddle.h"
#include "Ball.h"

#include "EffectBallFastBall.h"
#include "EffectBallSlowBall.h"
#include "EffectPaddleBigPaddle.h"
#include "EffectPaddleSmallPaddle.h"
#include "EffectBallFireBall.h"

EffectableSystem::EffectableSystem(Paddle* paddle, Ball* ball) : _paddle(paddle), _ball(ball)
{
	//Here we define the map between "tags" and their actual effects...

	_tagEffectMap.insert({ "NOTHING", std::make_shared<EffectBase>() });

	_tagEffectMap.insert({ "FAST_BALL", std::make_shared<EffectBallFastBall>(5.f, std::vector<std::string>({"SLOW_BALL"}), ball)});

	_tagEffectMap.insert({ "SLOW_BALL", std::make_shared<EffectBallSlowBall>(5.f, std::vector<std::string>({"FAST_BALL"}), ball) });

	_tagEffectMap.insert({ "BIG_PADDLE", std::make_shared<EffectPaddleBigPaddle>(5.f, std::vector<std::string>({"SMALL_PADDLE"}), paddle) });

	_tagEffectMap.insert({ "SMALL_PADDLE", std::make_shared<EffectPaddleSmallPaddle>(5.f, std::vector<std::string>({"BIG_PADDLE"}), paddle)});

	_tagEffectMap.insert({ "FIRE_BALL", std::make_shared<EffectBallFireBall>(5.f, std::vector<std::string>({}), ball) });
}

EffectableSystem::~EffectableSystem()
{

}

void EffectableSystem::update(float dt)
{
	//Tick down our active tags, removing if they are 0...

	for (auto &k : _effectActiveMap)
	{
		if (k.second <= 0.f)
			continue;

		k.second -= dt;


		//Effects will auto udo when their timer runs out
	}

	//Adding new effectables
	for (int i = 0; i < _effectQueue.size(); ++i)
	{
		std::string iStr = _effectQueue.front();
		_effectQueue.pop(); //I am still unsure why "pop" doesn't return a value in C++ STL

		std::weak_ptr<EffectBase> wp = _tagEffectMap.at(iStr);

		auto r = wp.lock();
		if (!r)
			return; //damn

		for (std::string mxStr : r->getMutexEffects())
		{
			//If an effect in here has a time above 0, we want to replace it!

			if (_effectActiveMap.find(mxStr) == _effectActiveMap.end())
				continue;

			_effectActiveMap[mxStr] = 0.f;

			std::weak_ptr<EffectBase> stop = _tagEffectMap.at(mxStr);
			auto s = stop.lock();
			if (!s)
				return; //damn again

			s->stopEffect();

		}

		//If we have this effect currently happening, we just want to reset the timer.
		//Else, add it and do it

		if (_effectActiveMap.find(iStr) == _effectActiveMap.end())
			_effectActiveMap.insert({ iStr, r->getMaxDuration() });
		else
			_effectActiveMap.at(iStr) = r->getMaxDuration();

		//We now apply the new effect
		r->applyEffect(); //note this is the EFFECT version of this function, not a loop here...

	}
}


std::string  EffectableSystem::getEffectText()
{
	std::string Out;

	for (auto i : _effectActiveMap)
	{
		if (i.second <= 0)
			continue;

		Out.append(i.first + ": " + std::to_string(i.second) + "\n");
	}

	return Out;
}