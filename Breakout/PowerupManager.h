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
    PowerupManager(Paddle* paddle, Ball* ball);
    ~PowerupManager();

    void update(float dt);
    void render(sf::RenderWindow& window);
    void spawnPowerup(); // Method to spawn a power-up
    void checkCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    int getPowerupCount() const;
    void resetPowerupCount();
    std::pair<POWERUPS, float> getPowerupInEffect();

private:
    Paddle* _paddle;
    Ball* _ball;
    std::vector<PowerupBase*> _powerups;            // used to manage deletion.
    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.
    int _powerupCount;
};
