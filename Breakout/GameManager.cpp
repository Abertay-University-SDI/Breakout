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

}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _failScreen = new FailScreen(_window, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::handleInput(float dt)
{
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused. Press r to restart.\nPress B to activate beast mode");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && _pause)
    {
        resetGame();
        _pause = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && _pause)
    {
        _paddle->setBeastMode(true);
        _pause = false;
        _masterText.setString("");
        _pauseHold = PAUSE_TIME_BUFFER;
    }

    //Check if game is being not being  played (win or loss state is true)
    if (_lives <= 0 || _levelComplete == true)
    {
        //Check for reset input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            resetGame();
        }

        return;
    }

    if (_pause)
    {
        return;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    if (_paddle->getMouseControl())
    {
        _paddle->mouseMove(sf::Mouse::getPosition().x);
    }

}

void GameManager::resetGame()
{
    //Reset all necessary variables
    if (_lives <= 0 || _pause == true)
    {
        _ball->setScore(0);
    }

    _brickManager->resetBricks();
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);

    _levelComplete = false;
    _pause = false;
    _lives = 3;
    _ball->resetBall();

    _paddle->reset();
    _ui->resetUI(INITIAL_LIVES);
    _masterText.setString("");
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _ui->updateScoreText(_ball->getScore());
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over. \nPress Space to play again.");
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed.  \nPress Space to continue.");
        return;
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

   
    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _failScreen->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    
    _failScreen->lifeLost(_lives);

}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _failScreen->render();

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
