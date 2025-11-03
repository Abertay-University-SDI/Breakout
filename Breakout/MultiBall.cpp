#include "MultiBall.h"


MultiBall::MultiBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball) : PowerupBase(window, paddle, ball)
{

}

MultiBall::~MultiBall()
{
}

std::pair<POWERUPS, float> MultiBall::applyEffect()
{
	for (int i = 0; i < 4; i++)
	{
		float offsetX = (rand() % 100) - 50;  // Random horizontal offset
		float offsetY = (rand() % 50) - 25;   // Random vertical offset

		Ball* newBall = new Ball(_window, 300.f, _gameManager, 400.f + offsetX, 300.f + offsetY);
		
		_gameManager->addBall(newBall);
	}
	
	return { Multiball, 5.0f };
}
