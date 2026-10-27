#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <algorithm>
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _state(GameState::Playing), _level(1), _time(0.f), _lives(INITIAL_LIVES),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile(FONT_PATH);
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _messagingSystem = std::make_unique<MessagingSystem>(_window);
    _ui = std::make_unique<UI>(_window, _lives, this);
    startLevel();
}

void GameManager::startLevel()
{
    _paddle = std::make_unique<Paddle>(_window);
    _brickManager = std::make_unique<BrickManager>(_window, this);
    _ball = std::make_unique<Ball>(_window, this);
    _powerupManager = std::make_unique<PowerupManager>(_window, _paddle.get(), _ball.get());

    int rows = std::min(BRICK_ROWS + _level - 1, BRICK_MAX_ROWS);
    _brickManager->createBricks(rows, BRICK_COLUMNS, BRICK_WIDTH, BRICK_HEIGHT, BRICK_PADDING);

    _time = 0.f;
    _timeLastPowerupSpawned = 0.f;
    _masterText.setString("");
    _state = GameState::Playing;
}

void GameManager::restart()
{
    _lives = INITIAL_LIVES;
    _level = 1;
    _ui = std::make_unique<UI>(_window, _lives, this);
    startLevel();
}

void GameManager::update(float dt)
{
    static bool pWasDown = false;
    static bool rWasDown = false;
    static bool enterWasDown = false;
    bool pDown = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    bool rDown = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    bool enterDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    bool pPressed = pDown && !pWasDown;
    bool rPressed = rDown && !rWasDown;
    bool enterPressed = enterDown && !enterWasDown;
    pWasDown = pDown;
    rWasDown = rDown;
    enterWasDown = enterDown;

    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;

    if (_state == GameState::GameOver)
    {
        _masterText.setString("Game over.\nPress R to restart.");
        if (rPressed) restart();
        return;
    }
    if (_state == GameState::LevelComplete)
    {
        _masterText.setString("Level " + std::to_string(_level) + " completed.\nPress Enter to continue.");
        if (enterPressed)
        {
            _level++;
            startLevel();
        }
        return;
    }
    if (pPressed)
    {
        _state = _state == GameState::Paused ? GameState::Playing : GameState::Paused;
        _masterText.setString(_state == GameState::Paused ? "paused." : "");
    }
    if (_state == GameState::Paused)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % POWERUP_SPAWN_ODDS == 0)
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    if (_window->hasFocus() && sf::Mouse::isButtonPressed(PADDLE_MOUSE_BUTTON))
        _paddle->setCentre(_window->mapPixelToCoords(sf::Mouse::getPosition(*_window)).x);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    if (_lives <= 0)
        _state = GameState::GameOver;

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
}

void GameManager::levelComplete()
{
    _state = GameState::LevelComplete;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui.get(); }
Paddle* GameManager::getPaddle() const { return _paddle.get(); }
BrickManager* GameManager::getBrickManager() const { return _brickManager.get(); }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager.get(); }
