#include "PowerupManager.h"


PowerupManager::PowerupManager(Paddle* paddle, Ball* ball)
    : _paddle(paddle), _ball(ball), _powerupCount(0)
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
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render(sf::RenderWindow& window)
{
    for (auto& powerup : _powerups)
    {
        powerup->render(window);
    }
}

void PowerupManager::spawnPowerup()
{

    // TODO finish this.
    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_paddle, _ball));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_paddle, _ball));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_paddle, _ball));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_paddle, _ball));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_paddle, _ball));
        break;
    case 5:
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
            _powerupCount++;
            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

int PowerupManager::getPowerupCount() const {
    return _powerupCount;
}

void PowerupManager::resetPowerupCount() {
    _powerupCount = 0;
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!_powerupInEffect) return { none, 0.f };
    return *_powerupInEffect;
}
