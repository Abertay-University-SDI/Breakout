#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none, 0.f }), _timeLastPowerupSpawned(0.f), _gameOverTimer(0.f), _isGameOver(false), _shakeDuration(0.f),
    _shakeMagnitude(0.f), _levelStarted(true), _levelStartTimer(3.f), _isBossLevel(false), _bossLevelStartTimer(0.f), _lifeLostTimer(0.f)
{
    _font.loadFromFile("font/menu_text.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition((windowWidth / 2), windowHeight / 2);
    _masterText.setCharacterSize(96);
    _masterText.setFillColor(sf::Color::Yellow);

    // Load sound buffers
    if (!_wallHitBuffer.loadFromFile("sounds/wall_hit.wav"))
    {
        std::cout << "Failed to load wall_hit.wav" << std::endl;
        // Replace with your sound file or handle error
    }
    if (!_paddleHitBuffer.loadFromFile("sounds/paddle_hit.wav"))
    {
        std::cout << "Failed to load paddle_hit.wav" << std::endl;
        // Replace with your sound file or handle error
    }
    if (!_brickHitBuffer.loadFromFile("sounds/brick_hit.wav"))
    {
        std::cout << "Failed to load brick_hit.wav" << std::endl;
        // Replace with your sound file or handle error
    }
    if (!_playerHitBuffer.loadFromFile("sounds/damage_hit.wav"))
    {
        std::cout << "Failed to load damage_hit.wav" << std::endl;
        // Replace with your sound file or handle error
    }
    _playerHitSound.setBuffer(_playerHitBuffer);
    _wallHitSound.setBuffer(_wallHitBuffer);
    _paddleHitSound.setBuffer(_paddleHitBuffer);
    _brickHitSound.setBuffer(_brickHitBuffer);

    if (!_menuMusic.openFromFile("sounds/menu_music.wav"))
    {
        std::cout << "Failed to load menu_music.wav" << std::endl;
    }

    if (!_gameMusic.openFromFile("sounds/game_music.wav"))
    {
        std::cout << "Failed to load game_music.wav" << std::endl;
    }

    if (!_bossMusic.openFromFile("sounds/boss_music.wav"))
    {
        std::cout << "Failed to load BossMusic.wav" << std::endl;
    }

    _menuMusic.setLoop(true);
    _gameMusic.setLoop(true);
    _bossMusic.setLoop(true);

    _menuMusic.setVolume(60.f);
    _gameMusic.setVolume(30.f);
    _bossMusic.setVolume(40.f);
}

void GameManager::initialize()
{
    delete _paddle;
    delete _ball;
    delete _brickManager;
    delete _powerupManager;
    delete _messagingSystem;
    delete _ui;

    _levelStarted = true;
    _levelStartTimer = 3.f;
    _isGameOver = false;
    _gameOverTimer = 0.f;
    _lives = 3;
    _time = 0.f;
    _levelComplete = false;
    _powerupInEffect = { none, 0.f };
    _timeLastPowerupSpawned = 0.f;
    _masterText.setString("");
    _shakeDuration = 0.f;
    _shakeMagnitude = 0.f;
    _bossLevelStartTimer = 0.f;
    _isBossLevel = false;
    _lifeLostTimer = 0.f;

    stopMusic();
    playGameMusic();

    std::cout << "Game Init" << std::endl;

    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this);
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this, _ball);

    _brickManager->createBricks(5, 12, 80.0f, 30.0f, 5.0f);
    _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);
    _ball->setDirection({ 0.f, 0.f });
}

void GameManager::update(float dt)
{
    if (_isGameOver)
    {
        _gameOverTimer -= dt;
        if (_gameOverTimer <= 0.f)
        {
            stopMusic();
            playMenuMusic();
        }
        return;
    }

    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;

    if (isBossLevel())
    {
        _powerupInEffect = { none, 0.f };
        _timeLastPowerupSpawned = 0.f;

        if (_bossLevelStartTimer > 0.f)
        {
            _bossLevelStartTimer -= dt;
            if (_bossLevelStartTimer <= 0.f)
            {
                _masterText.setString("");
                _ball->setDirection({ 0.f, 1.f });
                playBossMusic();
            }

            // Added paddle movement during boss countdown
            sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
            float windowWidth = static_cast<float>(_window->getSize().x);
            float paddleWidth = _paddle->getBounds().width;
            float paddleY = _paddle->getPosition().y;
            float newPaddleX = static_cast<float>(mousePos.x) - paddleWidth / 2.0f;
            newPaddleX = std::clamp(newPaddleX, 0.0f, windowWidth - paddleWidth);
            _paddle->setPosition(newPaddleX, paddleY);

            _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);
            _paddle->update(dt);
            _brickManager->update(dt);
            return;
        }
    }

    if (_levelComplete)
    {
        stopMusic();
        _masterText.setString("LEVEL COMPLETED");
        _masterText.setPosition((windowWidth / 2) - 295, windowHeight / 2 - 100);
        return;
    }

    if (_levelStarted)
    {
        _lifeLostTimer = 0.f;
        _levelStartTimer -= dt;
        _masterText.setString("GET READY! " + std::to_string(static_cast<int>(std::ceil(_levelStartTimer))));
        _masterText.setPosition((windowWidth / 2) - 200, windowHeight / 2 - 100);

        if (_levelStartTimer <= 0.f)
        {
            _levelStarted = false;
            _masterText.setString("");
            _ball->setDirection({ 0.f, 1.f });
        }

        _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);

        sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
        float windowWidth = static_cast<float>(_window->getSize().x);
        float paddleWidth = _paddle->getBounds().width;
        float paddleY = _paddle->getPosition().y;
        float newPaddleX = static_cast<float>(mousePos.x) - paddleWidth / 2.0f;
        newPaddleX = std::clamp(newPaddleX, 0.0f, windowWidth - paddleWidth);
        _paddle->setPosition(newPaddleX, paddleY);

        _paddle->update(dt);
        return;
    }

    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("PAUSED");
            _masterText.setPosition((windowWidth / 2) - 125, windowHeight / 2 - 100);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        enterFrenzy();
    }

    if (_shakeDuration > 0.f)
    {
        _shakeDuration -= dt;
        float offsetX = (static_cast<float>(rand()) / RAND_MAX * 2 - 1) * _shakeMagnitude;
        float offsetY = (static_cast<float>(rand()) / RAND_MAX * 2 - 1) * _shakeMagnitude;
        _shakeOffset = sf::Vector2f(offsetX, offsetY);
        _window->setView(sf::View(sf::FloatRect(_shakeOffset.x, _shakeOffset.y, _window->getSize().x, _window->getSize().y)));
    }
    else
    {
        _shakeOffset = sf::Vector2f(0.f, 0.f);
        _window->setView(sf::View(sf::FloatRect(0.f, 0.f, _window->getSize().x, _window->getSize().y)));
    }

    _time += dt;

    if (!_isBossLevel && _time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % RAND_POWERUP_TIME == 0)
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
    float windowWidth = static_cast<float>(_window->getSize().x);
    float paddleWidth = _paddle->getBounds().width;
    float paddleY = _paddle->getPosition().y;
    float newPaddleX = static_cast<float>(mousePos.x) - paddleWidth / 2.0f;
    newPaddleX = std::clamp(newPaddleX, 0.0f, windowWidth - paddleWidth);
    _paddle->setPosition(newPaddleX, paddleY);

    _paddle->update(dt);
    _brickManager->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);

    if (_lifeLostTimer > 0.f)
    {
        _lifeLostTimer -= dt;
        if (_lifeLostTimer <= 0.f && _masterText.getString() == "LIFE LOST!")
        {
            _masterText.setString("");
        }
    }

}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    playerHitSound();

    _shakeDuration = SHAKE_DURATION;
    _shakeMagnitude = SHAKE_MAGNITUDE;

    if (_lives > 0)
    {
        _masterText.setString("LIFE LOST!");
        _masterText.setPosition((windowWidth / 2) - 140, windowHeight / 2 - 100);
        _lifeLostTimer = LIFE_LOST_DISPLAY_TIME;
        _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);
        _ball->setDirection({ 0.f, 0.f });
    }

    if (_lives <= 0)
    {
        _isGameOver = true;
        _gameOverTimer = GAME_OVER_DISPLAY_TIME;
        _masterText.setString("GAME OVER");
        _masterText.setPosition((windowWidth / 2) - 185, windowHeight / 2 - 100);
        _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);
        _ball->setDirection({ 0.f, 0.f });
        return;
    }
}

void GameManager::enterFrenzy()
{
    _shakeDuration = FRENZY_DURATION;
    _shakeMagnitude = FRENZY_MAGNITUDE;
    getPowerupManager()->frenzyMode();
}

void GameManager::triggerShake(float duration, float magnitude)
{
    _shakeDuration = duration;
    _shakeMagnitude = magnitude;
}

void GameManager::playWallHitSound()
{
    _wallHitSound.play();
}

void GameManager::playPaddleHitSound()
{
    _paddleHitSound.play();
}

void GameManager::playBrickHitSound()
{
    _brickHitSound.play();
}

void GameManager::playerHitSound()
{
    _playerHitSound.play();
}

void GameManager::playMenuMusic()
{
    stopMusic();
    _menuMusic.play();
}

void GameManager::playGameMusic()
{
    stopMusic();
    _gameMusic.play();
}

void GameManager::playBossMusic()
{
    stopMusic();
    _bossMusic.play();
}

void GameManager::stopMusic()
{
    _menuMusic.stop();
    _gameMusic.stop();
    _bossMusic.stop();
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
    if (_isBossLevel)
    {
        _isGameOver = true;
        _gameOverTimer = GAME_OVER_DISPLAY_TIME;
        _masterText.setString("YOU WIN!");
        _masterText.setPosition((windowWidth / 2) - 150, windowHeight / 2 - 100);
        return;
    }
    else
    {
        _levelComplete = true;
        startBossLevel();
    }
}

void GameManager::startBossLevel()
{
    stopMusic();
    _levelComplete = false;
    _isBossLevel = true;
    _bossLevelStartTimer = BOSS_LEVEL_START_DELAY;
    _powerupManager->resetPowerups();
    _masterText.setString("BOSS FIGHT");
    _masterText.setPosition((windowWidth / 2) - 135, windowHeight / 2 - 100);
    _brickManager->createBossBrick();
    _ball->setPosition(_paddle->getPosition().x + _paddle->getBounds().width / 2.0f - 5, _paddle->getPosition().y - 150);
    _ball->setDirection({ 0.f, 0.f });
    _shakeDuration = 0.f;
    _shakeMagnitude = 0.f;
}

bool GameManager::isBossLevel() const
{
    return _isBossLevel;
}

bool GameManager::returnToMenu() const
{
    if (_isGameOver && _gameOverTimer <= 0)
    {
        return true;
    }
    return false;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }