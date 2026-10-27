#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr), _scoreManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f), _button(nullptr)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}
void GameManager::restartGame() {
    _time = 0.f;
    _lives = 3;
    _pauseHold = 0.f;
    _powerupInEffect = { none, 0.f };
    _timeLastPowerupSpawned = 0.f;
    _masterText.setString("");
    initialize();
}
void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _scoreManager = new ScoreManager(0);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);

    _button = new Button(_window);
    _button->setFillColor(sf::Color::Yellow);
    _button->setSize({ 300.f,50.f });
    _button->setPosition({ _window->getSize().x / 2 - 150.f, _window->getSize().y / 2 - 25.f });
    sf::Text* text = _button->getText();
    text->setCharacterSize(30);
    text->setFont(_font);
    text->setFillColor(sf::Color::Red);
    text->setPosition({ _window->getSize().x / 2 - 30.f, _window->getSize().y / 2 - 20.f });
    text->setString("Restart?");

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::handleInput() {
    if (_lives <= 0) {
        _button->handleInput();
    }
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        _button->setActive(true);
        if (_button->isClicked()) {
            restartGame();
        }
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.");
        _button->setActive(true);
        if (_button->isClicked()) {
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
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
    if (_lives == 0) {
        _button->render();
    }
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
ScoreManager* GameManager::getScoreManager() const { return _scoreManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
