#pragma once

#include <map>
#include <memory>
#include "SFML/Graphics.hpp"


class GameManager;
class Ball;

class BallManager 
{
public:
	BallManager(sf::RenderWindow* _window, GameManager* _gameManager, Ball* mainBall);
	~BallManager() = default;

	auto Update(float dt) -> void;
	auto Render() -> void;

	auto CreateBall(float velocity) -> void;
	auto KillBall(int _id) -> void;
	auto RemoveBalls() -> void;

	auto setMainBall(Ball* mainBall) -> void;
	auto getMainBall() -> Ball*;

private:

	//std::deque<std::unique_ptr<Ball>> balls;
	Ball* _mainBall;

	std::map<int, std::unique_ptr<Ball>> balls;
	GameManager* _gameManager;
	sf::RenderWindow* _window;

};