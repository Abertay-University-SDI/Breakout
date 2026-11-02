#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <random>
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupSmallPaddle.h"
#include "PowerupSlowBall.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "PowerupMultiBall.h"
#include "Paddle.h"
#include "Ball.h"

class GameManager;


class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, GameManager* gameManager);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    sf::RenderWindow* _window;
    Paddle* _paddle;
    std::vector<Ball*>& _balls;
    std::vector<PowerupBase*> _powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.
    std::mt19937 _rng; // mersenne twister

    GameManager* _gameManager;
};
