#include "BallManager.h"
#include "Ball.h"

#include "GameManager.h"
BallManager::BallManager(sf::RenderWindow* window, GameManager* gameManager, Ball* mainBall)
{
	_gameManager = gameManager;
	_window = window;
}

auto BallManager::Update(float dt) -> void
{
	for (auto& it : balls) 
	{
		it.second->update(dt);
	}
}

auto BallManager::Render() -> void
{
	for (auto& it : balls)
	{
		it.second->render();
	}
}

auto BallManager::CreateBall(float velocity) -> void
{
	//balls.push_back(std::unique_ptr<Ball>());
	
	
	if (!_mainBall)
		return;

	Ball* ball = new Ball(_window,velocity,_gameManager,splitBallColour);
		
	sf::Vector2f mainDirection = _mainBall->getDirection();
	sf::Vector2f mainPosition = _mainBall->getPosition();
	//might want some random stuff here

	ball->setDirection(mainDirection);
	ball->setPosition(mainPosition);
	
	balls[ball->GetID()] = std::make_unique<Ball>();
	balls[ball->GetID()].reset(ball);





}

auto BallManager::KillBall(int _id) -> void
{
	if (balls.contains(_id))
	{
		balls[_id]->setAlive(false);
	}
}

auto BallManager::RemoveBalls() -> void
{
	if (balls.empty())
		return;

	for (auto& it : balls) 
	{
		if(!it.second->getAlive())
			balls.erase(it.first);
	}
}

auto BallManager::setMainBall(Ball* mainBall) -> void
{
	_mainBall = mainBall;
}

auto BallManager::getMainBall() -> Ball*
{
	return _mainBall;
}

