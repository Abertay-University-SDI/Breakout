#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _paddle2(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
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
    _paddle = new Paddle(_window, sf::Color::Cyan);
    _paddle2 = new Paddle(_window, sf::Color::Red);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _paddle2, _ball);
    _ui = new UI(_window, _lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
	_ui->updateScoreText(_ball->getPaddle1Score(), _ball->getPaddle2Score());
    _powerupInEffect.second -= dt;

    //Sets whoever is winning to have a disadvantage in a when on top of eachother
    if (_ball->getPaddle1Score() > _ball->getPaddle2Score())
    {
        _paddle->lowerPaddle();
		_paddle2->returnToNormalHeight();
    }
    if (_ball->getPaddle1Score() < _ball->getPaddle2Score())
    {
        _paddle->returnToNormalHeight();
		_paddle2->lowerPaddle();
    }
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
        if (_ball->getPaddle1Score() > _ball->getPaddle2Score())
        {
            _masterText.setString("Player 1 wins!");
        }
        if (_ball->getPaddle1Score() > _ball->getPaddle2Score())
        {
            _masterText.setString("Player 2 wins!");
        }
        if (_ball->getPaddle1Score() == _ball->getPaddle2Score())
        {
            _masterText.setString("Its a tie!");
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
        //_powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // move paddle 2
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle2->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _paddle2->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    //_lives--;
    //_ui->lifeLost(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _paddle2->render();
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

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
Paddle* GameManager::getPaddle2() const { return _paddle2; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
