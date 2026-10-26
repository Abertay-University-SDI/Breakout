#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball), _rng(std::random_device{}())
{
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{

    std::uniform_real_distribution<float> xDist(
        _window->getSize().x * 0.05f,
        _window->getSize().x * 0.95f
    );

    float spawnX = xDist(_rng);

    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(std::make_unique<PowerupBigPaddle>(_window, _paddle, _ball, spawnX));
        break;
    case 1:
        _powerups.push_back(std::make_unique<PowerupSlowBall>(_window, _paddle, _ball, spawnX));
        break;
    case 2:
        _powerups.push_back(std::make_unique<PowerupFastBall>(_window, _paddle, _ball, spawnX));
        break;
    case 3:
        _powerups.push_back(std::make_unique<PowerupSmallPaddle>(_window, _paddle, _ball, spawnX));
        break;
    case 4:
        _powerups.push_back(std::make_unique<PowerupFireBall>(_window, _paddle, _ball, spawnX));
        break;
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            _powerupInEffect = powerup->applyEffect();
            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
