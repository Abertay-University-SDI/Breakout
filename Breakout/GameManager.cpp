#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _multiBall(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _ballCount(1), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this, 0, 300); 

    //Spawns a second ball outside of game window. Sets direction and colour
    _multiBall = new Ball(_window, 0.f, this, -100, 300);
    _multiBall->setDirection({ 0, 0 });

    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;

    //Moves second ball to first ball position when multiBall.  Creates the illusion of a ball being created.
    if (_powerupInEffect.first == multiball && _ballCount == 1)
    {
        _multiBall->setMultiBall(5.0f);
        _multiBall->setMultiColour();
        _multiBall->setMultiPosition(_ball->getBallPosition());
        _multiBall->setMultiVelocity(400.f);
        _multiBall->setDirection({1, 1});
        _ballCount++;
    }
    else if(_powerupInEffect.first == none && _ballCount == 2) //Moves the ball back off screen. Sets velocity and direction to zero.
    {
        _multiBall->setMultiPosition({ -100, 300 });
        _multiBall->setMultiVelocity(0.f);
        _multiBall->setDirection({ 0, 0 });
        _ballCount--;
    }


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _multiBall->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _multiBall->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
