#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>
#include <ctime>

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
}

void GameManager::initialize()
{
    // randomise seed
    srand(std::time(0));

    _screenShakeManager = new ScreenShakeManager(_window);
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, &normalBrickTex, &strongBrickTex, this);
    _messagingSystem = new MessagingSystem(_window);

    ballTex.loadFromFile("textures/ball.png");
    healthTex.loadFromFile("textures/heart.png");
    normalBrickTex.loadFromFile("textures/brick.png");
    strongBrickTex.loadFromFile("textures/brick2.png");

    _ball = new Ball(_window, _screenShakeManager, &ballTex, 400.0f, this);
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, &healthTex, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 66.0f, 26.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        _screenShakeManager->update(dt);
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        _screenShakeManager->update(dt);
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
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
    // switch to keyboard or mouse controls depending on whether the mouse has moved or a key is pressed
    if (usingMouseControls)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            usingMouseControls = false;
    }
    else
    {
        if (sf::Mouse::getPosition().x != lastMouseXPos)
            usingMouseControls = true;
    }
    
    // if usingMouseControls, set paddle x position based of mouse's x position relative to window position 
    if (usingMouseControls)
    {
        float windowScaleX = _window->getView().getSize().x / _window->getSize().x;
        int mousePosX = (sf::Mouse::getPosition().x - _window->getPosition().x) * windowScaleX;

        _paddle->setPositionX(mousePosX);
    }
    // else, move when A/D or left/right keys are pressed
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _paddle->moveLeft(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _paddle->moveRight(dt);
    }

    lastMouseXPos = sf::Mouse::getPosition().x;

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _screenShakeManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
}

void GameManager::debugPrint(int value)
{
    _ui->debugPrint(value);
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
    _screenShakeManager->render();
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
