#include <iostream>
#include "GamblingSystem.h"
#include "GameManager.h"
#include "GamblingOutcomeBase.h"
#include "GamblingOutcomeAddBall.h"
#include "Paddle.h"
#include "Ball.h"
#include "GamblingOutcomeEffect.h"

//It is worth noting: SFML (according to its  documentation) handles seeding random at start up, so its not something we need to worry about
GamblingSystem::GamblingSystem(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gameManager) : 
	_window(window), _paddle(paddle), _ball(ball), _gameManager(gameManager), _randMin(0), _randMax(0)
{
	//FOR NOW this is where we will fill our gambling outcomes

	_gamblingOutcomes.push_back(
	std::make_unique<GamblingOutcomeBase>(20, this)
	);

	_gamblingOutcomes.push_back(
		std::make_unique<GamblingOutcomeAddBall>(10, this, 3)
	);

	_gamblingOutcomes.push_back(
		std::make_unique<GamblingOutcomeEffect>(10, this, "FAST_BALL")
	);

	_gamblingOutcomes.push_back(
		std::make_unique<GamblingOutcomeEffect>(10, this, "BIG_PADDLE")
	);

	_gamblingOutcomes.push_back(
		std::make_unique<GamblingOutcomeAddBall>(1, this, 99)
	);

	_bActive = false;

	_gamblingCooldown = 0.f;


	initialise(); //TODO this just here?
}

//Setting up random device
void GamblingSystem::initialise()
{
	//Calculate the maximum of the random number generator, accounting for the weights of our gambling outcomes
	
	int TotalWeight = 0.f;
	for (int i = 0; i < _gamblingOutcomes.size(); ++i)
	{
		if (_gamblingOutcomes[i])
			TotalWeight += _gamblingOutcomes[i].get()->GetWeight();
	}

	_randMax = TotalWeight;

	//Initialise random device and uniform int distribution variables
	//TODO this could be a bit better
	_randomGenerator = std::mt19937(_rd());
	_distribution = std::uniform_int_distribution<>(_randMin, _randMax);
}

void GamblingSystem::update(float dt)
{
	//If we arent actively gambling, we want to ignore all this stuff
	if (!_bActive)
		return;

	//... or if we are not on time out, don't reduce the timer
	if (_gamblingCooldown <= 0)
	{
		_gameManager->updateGamblingUI(""); //Clear the gambling text here...
		_bActive = false;
		return;
	}

	//we will decrease the "time since gambled timer" here
	_gamblingCooldown -= dt;


}


void GamblingSystem::rollGamblingOutcome()
{
	//Presing the button won't do anything if we are on timeout
	if (_gamblingCooldown > 0)
		return;

	if (!_gameManager)
		return;

	_gamblingCooldown = 3.f;

	if (_gameManager->getLives() <= 0)
	{
		_gameManager->updateGamblingUI("NEED BALLS");
		return;
	}

	_gameManager->loseLife();
	std::cout << "Gambling!\n";
	_bActive = true;


	//Now the random roll itself
	int randomOut = _distribution(_randomGenerator);

	for (int i = 0; i < _gamblingOutcomes.size(); ++i)
	{
		const int W = _gamblingOutcomes[i].get()->GetWeight();
		if (randomOut <= W)
		{
			_gameManager->updateGamblingUI(_gamblingOutcomes[i].get()->activateOutcome());
			return;
		}
		randomOut -= W;
	}

	std::cout << "Uh the gambling system is not working guys\n";

}