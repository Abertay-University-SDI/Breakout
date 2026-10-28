#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class GameManager;


/*The gambling system, whenever the player presses the gambling hotkey bets a ball, and will roll a prize randomly.
This will then be applied to the player*/
class GamblingSystem
{
public:

	GamblingSystem(sf::RenderWindow* window, class Paddle* paddle, class Ball* ball, GameManager* gameManager);
	/*Initialisation function, seed the random number generator*/
	void initialise(); 

	/*Roll the dice, see what outcome you get! TODO MAKE JUCIER*/
	void rollGamblingOutcome();

	/*Update, tick down our timers for the system*/
	void update(float dt);

	/*Is the gambling system currently active ?*/
	bool _bActive;

	/*Cooldown timer to gamble again ? includes the animation*/
	float _gamblingCooldown;

private:

	/*NONE OWNING Ptr to the game window, allowing us to display things*/
	sf::RenderWindow* _window;

	/*NONE OWNING Ptr to the paddle, allowing us to do effects that alter the paddle*/
	class Paddle* _paddle;

	/*NONE OWNING Ptr to the ball, allowing us to do effects that alter the ball*/
	class Ball* _ball;


	/*NONE OWNING Ptr to the game manager*/
	GameManager* _gameManager;

	/*Maximum number our random generator can reach - i.e.: the sum of all the weights of all the outcomes*/
	int _randMax;

	/*Minimum number our random generator can reach - i.e.: 0*/
	int _randMin;

	/*Random number generator*/
	std::mt19937 _randomGenerator;

	/*Random device for rng*/
	std::random_device _rd;

	/*uniform int distribution for rng*/
	std::uniform_int_distribution<> _distribution;

	/*vector of all our outcomes*/
	std::vector<std::unique_ptr<class GamblingOutcomeBase>> _gamblingOutcomes;

public:

	/*GETTERS AND SETTERS*/

	inline GameManager* GetGameManager() { return _gameManager; }
};