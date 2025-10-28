#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include "Paddle.h"
#include "Ball.h"

#include "PowerupContainer.h"

class LivesCounter;

class PowerupManager
{
public:
    PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, LivesCounter* livesCounter);
    ~PowerupManager();

    void update(float dt);
    void render();
    void spawnPowerup(sf::Vector2f position); // Method to spawn a power-up
    void checkPlayerCollision(); // Check collision with paddle
    int getPowerupsSpawned();
    std::pair<POWERUPS, float> getPowerupInEffect();

    const std::vector<std::shared_ptr<BaseEffect>>& getEffects() { return _currentEffects; }
private:
    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    LivesCounter* _livesCounter;

    std::vector<PowerupContainer*> _powerups;

    std::vector<std::shared_ptr<BaseEffect>> _currentEffects;

    std::optional<std::pair<POWERUPS, float>> _powerupInEffect;    // used for gameManager to get reference.

    std::vector<PowerupContainer*> templatePowerups;
    void InitialisePowerups();
};
