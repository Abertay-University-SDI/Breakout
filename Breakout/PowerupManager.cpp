#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball), _rng(std::random_device{}())
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
    /*if (_powerupInEffect)
    {
        _powerupInEffect->second -= dt;
        if (_powerupInEffect->second <= 0)
        {
            _powerupInEffect.reset();
        }
    }*/

    // PowerupManager now checks if any of the powerups have just been activated and stores it in _powerupInEffect.
    _powerupInEffect.reset();

    checkCollision();   // Check if any of the powerups are touching the paddle.


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        //checkCollision(); // Don't know why this is in the for loop
        
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

    switch (rand() % 5)
    {
    case 0:
        _powerups.push_back(new PowerupBase(_window, _paddle, _ball, spawnX, {bigPaddle, 10.0f, paddleEffectsColour})); // Big Paddle
        break;
    case 1:
        _powerups.push_back(new PowerupBase(_window, _paddle, _ball, spawnX, {slowBall, 10.0f, ballEffectsColour}));  // Slow Ball
        break;
    case 2:
        _powerups.push_back(new PowerupBase(_window, _paddle, _ball, spawnX, {fastBall, 10.0f, ballEffectsColour}));  // Fast Ball
        break;
    case 3:
        _powerups.push_back(new PowerupBase(_window, _paddle, _ball, spawnX, {smallPaddle, 10.0f, paddleEffectsColour}));   // Small Paddle
        break;
    case 4:
        _powerups.push_back(new PowerupBase(_window, _paddle, _ball, spawnX, {fireBall, 10.0f, ballEffectsColour}));  // Fire Ball
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
