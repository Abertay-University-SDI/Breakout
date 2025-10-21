#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "PowerupBase.h"
#include "PowerupBigPaddle.h"
#include "PowerupSmallPaddle.h"
#include "PowerupSlowBall.h"
#include "PowerupFastBall.h"
#include "PowerupFireBall.h"
#include "Paddle.h"
#include "Ball.h"


class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    sf::RenderWindow* m_window;
    Paddle* m_paddle;
    Ball* m_ball;
    std::vector<PowerupBase*> m_powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> m_powerupInEffect;    // used for gameManager to get reference.
};
