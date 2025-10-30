#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), particleEffect(25)
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
    _ball = new Ball(_window, 400.0f, this); 
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
        _masterText.setString("Game over. Press (R) To Restart");

        //Add option to restart game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            //Restart Game
            restartGame();
        }

        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed. Press (R) To Play Again");

        //Add option to restart game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            //Restart Game
            restartGame();
        }
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
    _powerupManager->update(dt);
    if (particleEffectActive) {
        particleEffect.update();
    }
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    if (particleEffectActive) {
        particleEffect.render(*_window);
    }

    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::startParticleEffect(sf::Vector2f start, sf::Vector2f end)
{
    particleEffectActive = true;
    particleEffect.setEmitterLine(start, end);// = position;
}

void GameManager::restartGame()
{
    // Delete old objects, reset pointers, particle effect and the game states
    delete _paddle;
    delete _ball;
    delete _brickManager;
    delete _powerupManager;
    delete _messagingSystem;
    delete _ui;

    _paddle = nullptr;
    _ball = nullptr;
    _brickManager = nullptr;
    _powerupManager = nullptr;
    _messagingSystem = nullptr;
    _ui = nullptr;

    _time = 0.f;
    _lives = 3;
    _pauseHold = 0.f;
    _levelComplete = false;
    _powerupInEffect.first = none;
    _powerupInEffect.second = 0.f;
    _timeLastPowerupSpawned = 0.f;

    particleEffectActive = false;
    particleEffect = ParticleEffect(25);


    _masterText.setString("");

    // Reinitialize everything
    initialize();

}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
