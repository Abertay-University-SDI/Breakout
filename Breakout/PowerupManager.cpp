#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball)
{
    powerUpBigTex.loadFromFile("textures/powerUpBig.png");
    powerUpSmallTex.loadFromFile("textures/powerUpSmall.png");

    powerUpFastTex.loadFromFile("textures/powerUpFast.png");
    powerUpSlowTex.loadFromFile("textures/powerUpSlow.png");

    powerUpFireTex.loadFromFile("textures/powerUpFire.png");
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
    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball, &powerUpBigTex));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball, &powerUpSlowTex));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball, &powerUpFastTex));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball, &powerUpSmallTex));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball, &powerUpFireTex));
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
