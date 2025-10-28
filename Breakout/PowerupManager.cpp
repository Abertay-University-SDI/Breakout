#include "PowerupManager.h"

#include <iostream>



PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, LivesCounter* livesCounter)
    : _window(window), _paddle(paddle), _ball(ball), _livesCounter{livesCounter}
{
    InitialisePowerups();
}

PowerupManager::~PowerupManager()
{
    for (PowerupContainer* container : _powerups)
    {
        delete container;
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

    checkPlayerCollision();

    //Update and clean up powerups
    for (auto it = _powerups.begin(); it != _powerups.end();)
    {
        (*it)->Update(dt);
        if ((*it)->ShouldBeDestroyed())
        {
            delete *it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //Update and clean up effects
    for (auto it = _currentEffects.begin(); it != _currentEffects.end();)
    {
        (*it)->UpdateEffect(dt);
        if ((*it)->ShouldBeDestroyed())
        {
            it = _currentEffects.erase(it);
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
        powerup->Render();
    }
}

void PowerupManager::spawnPowerup(sf::Vector2f position)
{
    //Pick random powerup from vector
    int randomNumber = rand() % templatePowerups.size();
    PowerupContainer* randomPowerup = templatePowerups[randomNumber];

    //Copy random powerup
    PowerupContainer* powerup = new PowerupContainer(*randomPowerup);
    _powerups.push_back(powerup);
    powerup->SetPosition(position);
}

void PowerupManager::checkPlayerCollision()
{
    for (auto& powerup : _powerups)
    {
        if (powerup->CheckCollisionWithPaddle(_paddle))
        {
            //Powerup collided, get it's effects
            _currentEffects.insert(_currentEffects.begin(), powerup->getEffects().begin(), powerup->getEffects().end());
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

void PowerupManager::InitialisePowerups()
{
    PowerupContainer* fastBall = new PowerupContainer(_window, sf::Color::Yellow);
    PowerupContainer* slowBall = new PowerupContainer(_window, sf::Color::Blue);
    PowerupContainer* bigPaddle = new PowerupContainer(_window, sf::Color(155,0,255));
    PowerupContainer* smallPaddle = new PowerupContainer(_window, sf::Color::Green);
    PowerupContainer* fastPaddle = new PowerupContainer(_window, sf::Color::Cyan);
    PowerupContainer* slowPaddle = new PowerupContainer(_window, sf::Color(255, 128, 128));
    PowerupContainer* fireBall = new PowerupContainer(_window, sf::Color::Red);
    PowerupContainer* bigBall = new PowerupContainer(_window, sf::Color::Magenta);
    PowerupContainer* smallBall = new PowerupContainer(_window, sf::Color::White);
    PowerupContainer* stickyBall = new PowerupContainer(_window, sf::Color(174,159,104),15.0f);
    PowerupContainer* godModeBall = new PowerupContainer(_window, sf::Color(137,80,47));

    PowerupContainer* extraLife = new PowerupContainer(_window, sf::Color(128,255,128),0.0f);

    fastBall->AddEffect(new BallSpeedEffect(_ball, 2.0f));
    fastBall->AddEffect(new BallSizeEffect(_ball, 0.85f));
    slowBall->AddEffect(new BallSpeedEffect(_ball, 0.5f));
    slowBall->AddEffect(new BallSizeEffect(_ball, 1.10f));

    bigPaddle->AddEffect(new PaddleSizeEffect(_paddle, 1.5f));
    smallPaddle->AddEffect(new PaddleSizeEffect(_paddle, 0.67f));
    fastPaddle->AddEffect(new PaddleSpeedEffect(_paddle, 2.0f));
    slowPaddle->AddEffect(new PaddleSpeedEffect(_paddle, 0.5f));

    fireBall->AddEffect(new FireBallEffect(_ball));
    fireBall->AddEffect(new BallSpeedEffect(_ball, 1.15f));

    bigBall->AddEffect(new BallSizeEffect(_ball, 2.0f));
    bigBall->AddEffect(new BallSpeedEffect(_ball, 0.65f));
    smallBall->AddEffect(new BallSizeEffect(_ball, 0.5f));
    smallBall->AddEffect(new BallSpeedEffect(_ball, 1.15f));

    stickyBall->AddEffect(new StickyBallEffect(_ball));
    godModeBall->AddEffect(new GodModeEffect(_ball));
    godModeBall->AddEffect(new FireBallEffect(_ball));
    godModeBall->AddEffect(new BallSpeedEffect(_ball, 2.0f));

    extraLife->AddEffect(new ExtraLifeEffect(_livesCounter));

    templatePowerups.push_back(fastBall);
    templatePowerups.push_back(slowBall);
    templatePowerups.push_back(bigPaddle);
    templatePowerups.push_back(smallPaddle);
    templatePowerups.push_back(fastPaddle);
    templatePowerups.push_back(slowPaddle);
    templatePowerups.push_back(fireBall);
    templatePowerups.push_back(bigBall);
    templatePowerups.push_back(smallBall);
    templatePowerups.push_back(stickyBall);
    templatePowerups.push_back(godModeBall);
    templatePowerups.push_back(extraLife);
}