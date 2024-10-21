#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

#pragma region DEFINE PAUSE

//Improvements to pausing.
enum class GameState {
    Running,
    Paused,
    Transitioning
};

GameState _gameState = GameState::Running;

#pragma endregion

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

    /////////////// PAUSE LOGIC \\\\\\\\\\\\\\\\\\
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
        
    handlePauseInput();

    if (_gameState == GameState::Paused) {
        return;
    }

    /////////////// Screen Shake Logic \\\\\\\\\\\\\\\\
    //Screen shake

    if (_shakeDuration > 0) {
        _shakeOffset.x = (rand() % 200 - 100) / 100.0f * _shakeIntensity;
        _shakeOffset.y = (rand() % 200 - 100) / 100.0f * _shakeIntensity;

        _shakeDuration -= dt;
    }
    else 
    {
        _shakeOffset = { 0.0f, 0.0f };
    }

    sf::View view = _window->getView();
    view.setCenter(view.getCenter() + _shakeOffset);
    _window->setView(view);
    
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
    initiateShake(0.15f, 0.4f);
}

void GameManager::initiateShake(float duration, float intensity) {
    _shakeDuration = duration;
    _shakeIntensity = intensity;
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


void GameManager::handlePauseInput() 
{
    static bool wasPressed = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        if (!wasPressed) {
            wasPressed = true;

            if (_gameState == GameState::Running && _pauseHold <= 0.0f) {
                _gameState = GameState::Paused;
                _masterText.setString("Paused. ");
                _pauseHold = PAUSE_TIME_BUFFER;
            }
            else if (_gameState == GameState::Paused && _pauseHold <= 0.0f) {
                _gameState = GameState::Running;
                _masterText.setString("");
                _pauseHold = PAUSE_TIME_BUFFER;
            }
        }
    }
    else 
    {
        wasPressed = false; //reset the key press
    }
}


sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
