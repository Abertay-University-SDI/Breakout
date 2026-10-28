#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(36);
    _masterText.setFillColor(sf::Color::Cyan);
}

void GameManager::initialize()
{
    // Set master string on game start
    _masterText.setString("");

    // Set lives on game start
    _lives = 3;

    _cameraManager = new CameraManager(_window);
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, false, this); 
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
        _gameOver = true;
        _lifeLost = false; // This check is mainly here so the screen doesn't shake on restart
        scoreCount();
        _masterText.setString("GAME OVER | BRICKS LEFT: " + _bricksTotal + " | HIGH SCORE: " + _scoreDisplay);
        
    }
    if (_gameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            _gameOver = false;
            _masterText.setString("");
            initialize();
        }
        return;
    }
    if (_levelComplete)
    {
        scoreCount();
        _masterText.setString("LEVEL COMPLETED");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            initialize();
            _levelComplete = false;
        }
        return;
    }

    if (_lifeLost) {
        _cameraManager->screenShake(0.2f, 1000.f);
        _lifeLost = false;
        return;
    }

    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("PAUSED");
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

    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % 700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _paddle->moveLeft(dt);

    // update everything
    _cameraManager->update(dt);
    _ball->update(dt);
    _paddle->update(dt);
    _powerupManager->update(dt);

    if (_isMultiBall)
    {
        for (int i = 0; i < 3; i++)
        {
            _extraBalls[i]->update(dt);
        }
    }
    
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    _lifeLost = true;
}

void GameManager::gainLife()
{
    if (_lives < 3) {
        _ui->lifeGained(_lives);
        _lives++;
    }
}

void GameManager::render()
{
    if (!_gameOver) { // Quick fix to prevent any balls from appearing on game over
        _ball->render();

        if (_isMultiBall)
        {
            for (int i = 0; i < 3; i++)
            {
                _extraBalls[i]->render();
            }
        }
    }
    _paddle->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::multiBall(bool value)
{
    _isMultiBall = value;

    if (_isMultiBall)
    {
        for (int i = 0; i < 3; i++)
        {
            _extraBalls[i] = new Ball(_window, 400.0f, true, this);
        }
    }

}

void GameManager::gameOver()
{
    _gameOver = true;
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::scoreCount()
{
    // Getting bricks still remaining
    _bricksRemaining = (_brickManager->getBricks()).size();
    int _bricksDestroyed = 50 - _bricksRemaining;
    if (_bricksDestroyed > _highScore) {
        _highScore = _bricksDestroyed;
    }
    _bricksTotal = std::to_string(_bricksRemaining);
    _scoreDisplay = std::to_string(_highScore);
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
