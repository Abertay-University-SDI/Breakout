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

void PowerupManager::reset()
{
    _powerupInEffect.reset();
    _powerups.clear();
    _powerupTimeExtendCount = 0;
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

    // TODO finish this.
    switch (rand() % 6)
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
    case 5:
        _powerups.push_back(new PowerupTimeExtender(_window, _paddle, _ball));
        break;
    default:
       break;
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            auto acquiredPowerup = powerup->applyEffect(1.0f + (_powerupTimeExtendCount * 0.25f));

            // increment number of time extensions when a time extender is collected
            if (acquiredPowerup.first == timeExtend) {
                _powerupTimeExtendCount++;
            }
            _powerupInEffect = acquiredPowerup;
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
