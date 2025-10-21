#pragma once

#include <optional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupSlowBall.h"
#include "PowerupSmallPaddle.h"


class PowerupManager
{
public:
	PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
	~PowerupManager();

	void update(float dt);
	void render();
	void spawnPowerup();   // Method to spawn a power-up
	void checkCollision(); // Check collision with paddle
	int getPowerupsSpawned();
	std::pair<POWERUPS, sf::Vector2f> getPowerupInEffect();

private:
	sf::RenderWindow* _window;
	Paddle* _paddle;
	Ball* _ball;
	std::vector<PowerupBase*> _powerups; // used to manage deletion.
	std::optional<std::pair<POWERUPS, sf::Vector2f>> _powerupInEffect;
	// used for gameManager to get reference.
};
