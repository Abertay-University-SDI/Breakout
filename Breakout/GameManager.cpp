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
    delete _paddle;
	delete _ball;
	delete _brickManager;
	delete _powerupManager;
	delete _messagingSystem;
	delete _ui;


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
    _ui->updateShake();

    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    

    if (_lives <= 0)
    {
        _masterText.setString("Game over. \n\nPress ESC to quit or \nPress R to play again");
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            _lives = 3;
            _levelComplete = false;

            _masterText.setString("");
            initialize();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window->close();
        }
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed. \n\nPress ESC to quit or \nPress R to play again");

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            _lives = 3;
            _levelComplete = false;
            
            _masterText.setString("");
            initialize();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window->close();
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
            _masterText.setString("Paused.");
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

    // Handle Particle
    for (auto it = _particles.begin(); it != _particles.end(); ) {
        it->particleShape.move(it->velocity * dt);
        it->lifetime -= dt;

        // Fade out
        sf::Color color = it->particleShape.getFillColor();
        if (it->lifetime > 0.f) {
            color.a = static_cast<sf::Uint8>(255 * (it->lifetime / 2.0f)); // fade
            it->particleShape.setFillColor(color);
            ++it;
        }
        else {
            it = _particles.erase(it); // remove expired particle
        }
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand() % POWERUP_SPAWN_CHANCE == 0)      // TODO parameterise
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
    _ui->setIsShaking(true);
    _ui->startShake(10.0f, 0.5f);
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);

    for (const auto& p : _particles) {
        _window->draw(p.particleShape);
    }

    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

void GameManager::particleEffect(sf::Vector2f position)
{
    const int particleCount = 500;

    for (int i = 0; i < particleCount; ++i) {
        Particle p;
        p.particleShape = sf::CircleShape(3.f);
        p.particleShape.setFillColor(sf::Color::Yellow);
        p.particleShape.setPosition(position);

        float angle = (std::rand() % 360) * 3.14 / 180.f;
        float speed = ((std::rand() % 100) / 10.f + 50.f); // 50 to 60

        p.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        p.lifetime = 1.0f + (std::rand() % 100) / 100.f;

        _particles.push_back(p); // store in member vector
    }
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
