#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Cyan);//changed colour
}

void GameManager::initialize()
{
    _levelComplete = false;
    //delete on reinitialise
    delete _paddle;
    delete _brickManager;
    delete _messagingSystem;
    delete _ball;
    delete _powerupManager;
    delete _ui;

    _masterText.setString("press 'p' to play");
    powerupSpawnRate = 1;
    powerupSpawn = 0;

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);

    _lives = 3;
    _ui = new UI(_window, _lives, this);

    //start the game off paused
    _pause = true;
    
    // Create bricks
    _brickManager->createBricks(1, 1, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    _shake.update(dt);

    if (_lives <= 0)
    {
        _masterText.setString("Game over. Space to restart\nPress escape to exit");
        delete _ball;
        _ball = nullptr;
        powerupSpawn = powerupSpawnRate +1;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed. Space to restart\nPress escape to exit");
        delete _ball;
        _ball = nullptr;
        powerupSpawn = powerupSpawnRate + 1;
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

    //restart game at any time if space is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) initialize();

    //closes game at any time if escape is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) _window->close();
    
    // timer.
    _time += dt;

    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%powerupSpawnRate == powerupSpawn)
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle - added dual controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    if(_ball) _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    
    //amplitude, duration (s), frequency
    _shake.trigger(40.f, 0.5f, 18.f);
}

void GameManager::render()
{
    //shake it   
    sf::View worldView = _window->getDefaultView();
    worldView.setCenter(worldView.getCenter() + _shake.offset());
    _window->setView(worldView);

    _paddle->render();
    if(_ball)_ball->render();
    _brickManager->render();
    _powerupManager->render();

    _window->setView(_window->getDefaultView()); //reset after shake
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