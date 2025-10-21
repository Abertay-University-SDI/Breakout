#include "PowerupManager.h"

PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball)
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
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
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
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
    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
        break;
    }
}

void PowerupManager::frenzyMode()
{
    _ball->setFrenzyBall(3.0f);
    _ball->setVelocity(1.5f, 3.0f);
    _powerupInEffect = std::make_pair(frenzyBall, 3.0f);
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

void PowerupManager::resetPowerups()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
    _powerupInEffect.reset();

    _ball->setVelocity(1.0f, 0.f); 
    _ball->setFireBall(0.f); 
    _ball->setFrenzyBall(0.f); 
    _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);

    _paddle->setWidth(1.0f, 0.f); 
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