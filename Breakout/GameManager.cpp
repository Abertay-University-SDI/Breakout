#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"

GameManager::GameManager()
    : _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _nextPowerUpTime(POWERUP_MIN_TIME), _screenShakePower(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle();
    _brickManager = new BrickManager(this);
    _messagingSystem = new MessagingSystem();
    _ball = new Ball(400.0f, this); 
    _powerupManager = new PowerupManager(_paddle, _ball);
    _ui = new UI(_lives, this);

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    // Update screen shake
    _screenShakePower -= dt;
    if (_screenShakePower < 0.0f) {
        _screenShakePower = 0.0f;
    }
    
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    // Update lives
    if (_lives == INITIAL_LIVES) {
        _powerupManager->resetPowerupCount();
    }
    else if (_powerupManager->getPowerupCount() >= POWERUP_COUNT_FOR_LIFE) {
        _lives++;
        _ui->setLives(_lives);
        _powerupManager->resetPowerupCount();
    }
    _ui->setNewLifeFraction(_powerupManager->getPowerupCount() / (float)POWERUP_COUNT_FOR_LIFE);
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


    if (_time > _nextPowerUpTime)
    {
        _powerupManager->spawnPowerup();
        _nextPowerUpTime += POWERUP_MIN_TIME + (rand() / (double) RAND_MAX) * (POWERUP_MAX_TIME - POWERUP_MIN_TIME);
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
    _ui->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->setLives(_lives);

    addScreenShake(0.25f);
}

void GameManager::render(sf::RenderWindow& window)
{
    {// Update view based on window size
        sf::Vector2f viewportDim(1, 1);
        float windowAspect = window.getSize().x / (float)window.getSize().y;
        float cameraAspect = GAME_DIMENSIONS.x / (float)GAME_DIMENSIONS.y;
        if (windowAspect > cameraAspect) {// Too wide = black bars on the sides
            viewportDim.x = cameraAspect / windowAspect;
        } else {// Too tall = black bars on the top and bottom
            viewportDim.y = windowAspect / cameraAspect;
        }
        sf::View view(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(GAME_DIMENSIONS)));
        view.setViewport(sf::FloatRect(sf::Vector2f(0.5f, 0.5f) - viewportDim * 0.5f, viewportDim));
        window.setView(view);
    }
    {// Adjust view based on screen shake
        sf::View view = window.getView();
        sf::Vector2f shake(
            _screenShakePower * (rand() % 81 - 40),
            _screenShakePower * (rand() % 81 - 40)
        );
        view.setCenter(sf::Vector2f(GAME_DIMENSIONS) * 0.5f + shake);
        window.setView(view);
    }
    {// Draw background (the clear color is black to create black bars)
        sf::RectangleShape background(window.getView().getSize());
        background.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.0f);
        background.setFillColor(sf::Color(20, 20, 30));
        window.draw(background);
    }
    _paddle->render(window);
    _ball->render(window);
    _brickManager->render(window);
    _powerupManager->render(window);
    {// Stop screen shake from affecting UI
        sf::View view = window.getView();
        view.setCenter(sf::Vector2f(GAME_DIMENSIONS) * 0.5f);
        window.setView(view);
    }
    window.draw(_masterText);
    _ui->render(window);
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::addScreenShake(float amount) {
    if (amount > _screenShakePower) {
        _screenShakePower = amount;
    }
}

UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
