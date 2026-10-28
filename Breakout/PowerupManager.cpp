#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, EffectableSystem* effectableSystem)
    : _window(window), _paddle(paddle), _ball(ball), _rng(std::random_device{}()), _effectableSystem(effectableSystem)
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

    //These seperate objects now just dictate the colours of the balls - we could also add behaviour for how they fall differently if we so wished
    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball, spawnX, "BIG_PADDLE", _effectableSystem));
        break;
    case 1:
        _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball, spawnX, "SLOW_BALL", _effectableSystem));
        break;
    case 2:
        _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball, spawnX, "FAST_BALL", _effectableSystem));
        break;
    case 3:
        _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball, spawnX, "SMALL_PADDLE", _effectableSystem));
        break;
    case 4:
        _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball, spawnX, "FIRE_BALL", _effectableSystem));
        break;
    }
}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            powerup->setAlive(false); //depreceated
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
