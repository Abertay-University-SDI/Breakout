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
    _masterText.setFillColor(sf::Color::Yellow);

    _windowCenter = _window->getView().getCenter();
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
        _masterText.setString("Game over. Press G to replay");

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
            Reset();
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        return;
    }

    //shakes screen when life is lost
    if (_shaking)
    {
        _screenShakeDuration -= dt; //countdown duration

        if (_screenShakeDuration > 0)
        {
            //create an offset to move the screen by
            float offsetX = ((rand() % 10 - 5) * _shakePower);
            float offsetY = ((rand() % 10 - 5) * _shakePower);

            //apply these offests to the viewport
            sf::View view = _window->getView(); //gets the current viewport being used
            view.setCenter(_windowCenter + sf::Vector2f(offsetX, offsetY)); //centers it at the offset
            _window->setView(view);
        }
        else
        {
            _shaking = false;   //breaks loop if duraion ends

            //returns to original window and viewport positios 
            sf::View view = _window->getView();
            view.setCenter(_windowCenter);
            _window->setView(view);
        }
    }

    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("Press P to return to game");
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


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % _powerupChance == 0)
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
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake.
    _shaking = true;    //begin screen shake
    _screenShakeDuration = 0.8f;    //continue for 0.8 secs
}

void GameManager::render()
{
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

void GameManager::Reset()
{
    //set variabkes back to default
    _lives = 3;
    _time = 0.f;
    _pause = false;
    _pauseHold = 0.f;
    _levelComplete = false;
    _powerupInEffect = { none, 0.f };
    _timeLastPowerupSpawned = 0.f;

    //delete ball, paddles and bricks
    delete _ball;
    delete _paddle;
    delete _brickManager;
    delete _ui;

    //create new instances for them
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
    _ball = new Ball(_window, 400.0f, this);
    _ui = new UI(_window, _lives, this);

    //hide text
    _masterText.setString("");
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
