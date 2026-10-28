#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _effectableSystem(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false), _gamblingSystem(nullptr),
 _timeLastPowerupSpawned(0.f)
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
    _effectableSystem = new EffectableSystem(_paddle, _ball);
    _powerupManager = new PowerupManager(_window, _paddle, _ball, _effectableSystem);

    _ui = new UI(_window, _lives, this);
    _gamblingSystem = new GamblingSystem(_window, _paddle, _ball, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _gamblingSystem->update(dt);
    _effectableSystem->update(dt);
    _powerupManager->update(dt);

    if (_lives < 0)
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


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%1 == 0)      // TODO parameterise
    {
        _timeLastPowerupSpawned = _time;

        _powerupManager->spawnPowerup(); //Spawn in the orb...
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    {
        _gamblingSystem->rollGamblingOutcome();
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);


    _ui->updatePowerupText(_effectableSystem->getEffectText());
}

void GameManager::updateGamblingUI(std::string str)
{
    if (_ui)
        _ui->updateGamblingText(str);
}
void GameManager::addLives(int lives)
{
    _lives += lives;
    _ui->updateLivesText(_lives);
}
void GameManager::loseLife()
{
    _lives--;
    _ui->updateLivesText(_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _window->draw(_masterText);
    _ui->render();
    _powerupManager->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
