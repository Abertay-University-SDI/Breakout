#pragma once
#include <SFML/Graphics.hpp>
#include "GamblingSystem.h"
#include "GameManager.h"

/*The base class from which we derrive our functionality for gambling outcomes.
Essentially, each outcome just has a weight for helping to decide which one is picked, and a virtual function that essentially is "do the thing" - activating a powerups effect.
They will be passed in the game manager to allow them to acccess functionality that way.
*/

class GamblingOutcomeBase
{
public:
	GamblingOutcomeBase();


	GamblingOutcomeBase(int Weight, GamblingSystem* gamblingSystem);

	/*Virtual function for activating the outcome - the base one does nothing*/
	virtual std::string activateOutcome();

protected:

	GamblingSystem* _gamblingSystem;

	//What text gets added to the screen when this outcome happens?
	std::string _outcomeString;

	//Value dictating the likelihood that this outcome  occours
	int _weight;

public:


	/*GETTERS AND SETTERS*/
	inline int GetWeight() { return _weight; }
};