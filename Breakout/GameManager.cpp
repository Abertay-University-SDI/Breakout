#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include "Raymarch.h"
#include <algorithm>
#include <iostream>
#include <string>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(INITIAL_LIVES), _pauseHold(0.f),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f),
    _shakeStrength(0.f), _shakeDuration(0.f), _shakeTime(0.f), _particles(nullptr),
    _state(GameState::Serving), _spaceHeld(false), _level(1), _score(0)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    Raymarch::init();
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
    _particles = new Particles(_window, _paddle);

    startLevel(1);
}

void GameManager::newGame()
{
    _lives = INITIAL_LIVES;
    _score = 0;
    _ui->resetLives(_lives);
    startLevel(1);
}

// Fresh bricks, powerups cleared, ball back on the paddle. Each level adds a row and speeds up the ball.
void GameManager::startLevel(int level)
{
    _level = level;
    _state = GameState::Serving;
    _brickManager->createBricks(std::min(4 + level, MAX_BRICK_ROWS), BRICK_COLUMNS, 80.0f, 30.0f, 5.0f);
    _powerupManager->clear();
    _paddle->setWidth(1.0f, 0.0f);
    _ball->setSpeedScale(1.0f + LEVEL_SPEEDUP * (level - 1));
    _ball->reset();
    _timeLastPowerupSpawned = _time;
    _ui->updateScore(_score, _level);
}

// points are worth more on later levels
void GameManager::addScore(int points)
{
    _score += points * _level;
    _ui->updateScore(_score, _level);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;

    // effects keep playing after game over / level complete, but freeze on pause
    if (_shakeTime > 0.f) _shakeTime -= dt;
    if (!_pause) _particles->update(dt);

    // only act on SPACE the frame it goes down, so one press doesn't skip several screens
    bool spaceDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    bool spacePressed = spaceDown && !_spaceHeld;
    _spaceHeld = spaceDown;

    if (_state == GameState::GameOver)
    {
        if (spacePressed) newGame();
        return;
    }
    if (_state == GameState::LevelComplete)
    {
        if (spacePressed) startLevel(_level + 1);
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // serve
    if (_state == GameState::Serving && spacePressed)
    {
        _ball->launch();
        _state = GameState::Playing;
    }

    // timer.
    _time += dt;


    if (_state == GameState::Playing && _time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
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

    shake(15.f, 0.4f);

    _state = (_lives <= 0) ? GameState::GameOver : GameState::Serving;
}

void GameManager::shake(float strength, float duration)
{
    // a weaker shake never cuts a stronger one short
    if (_shakeTime > 0.f && _shakeStrength * _shakeTime / _shakeDuration > strength) return;
    _shakeStrength = strength;
    _shakeDuration = duration;
    _shakeTime = duration;
}

void GameManager::render()
{
    // Screen shake: jitter the view, fading out over the shake's duration.
    sf::View view = _window->getDefaultView();
    if (_shakeTime > 0.f)
    {
        float strength = _shakeStrength * _shakeTime / _shakeDuration;
        view.move((rand() / (float)RAND_MAX * 2.f - 1.f) * strength, (rand() / (float)RAND_MAX * 2.f - 1.f) * strength);
    }
    _window->setView(view);

    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _particles->render();
    Raymarch::draw(*_window);
    updateMessage();
    _window->draw(_masterText);
    _ui->render();
}

// Centre-screen prompt for whatever the player should do next.
void GameManager::updateMessage()
{
    std::string message;
    if (_pause)
        message = "Paused";
    else if (_state == GameState::Serving)
        message = "Level " + std::to_string(_level) + "\nPress SPACE to launch";
    else if (_state == GameState::LevelComplete)
        message = "Level " + std::to_string(_level) + " cleared!\nPress SPACE for level " + std::to_string(_level + 1);
    else if (_state == GameState::GameOver)
        message = "Game over - score " + std::to_string(_score) + "\nPress SPACE to play again";

    if (message != _masterText.getString())
    {
        _masterText.setString(message);
        sf::FloatRect bounds = _masterText.getLocalBounds();
        _masterText.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
    }
    sf::Vector2f centre = _window->getView().getCenter();
    _masterText.setPosition(centre.x, centre.y + 60.f);
}

void GameManager::levelComplete()
{
    if (_state == GameState::Playing)
        _state = GameState::LevelComplete;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
Particles* GameManager::getParticles() const { return _particles; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
