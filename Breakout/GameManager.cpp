#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include "AudioMananger.h"
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
    AudioMananger::getInstance();
	_parralaxBG = new ParralaxBG();
	_parralaxBG->addLayer("../assets/back.png", 0.1f);
    _parralaxBG->addLayer("../assets/buildings.png", 0.4f);
    _parralaxBG->addLayer("../assets/front.png", 0.7f);
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this,sf::Color::Cyan); 
	_ball->setPrimary(true);
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this);
	
    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f, 1);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    if(_powerupInEffect.first == POWERUPS::addBall)
    {
        addExtraBall();
    }
	else
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
	

    if (_lives <= 0)
    {
        _masterText.setString("Game over.");
        return;
    }
    if (_levelComplete)
    {
		nextLevel();
    }
    while(_countdown > 0.f)
    {
        _countdown -= dt;
        _masterText.setString("Level " + std::to_string(_level) + " starting in " + std::to_string((int)_countdown + 1));
        return;
	}
	_masterText.setString("");
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
    float beforeMove = _paddle->getPosition().x;
    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
	
    _paddle->update(dt);
	float deltaMove = _paddle->getPosition().x - beforeMove;
    _parralaxBG->update(deltaMove, dt);
    _ball->update(dt);
    for(auto& extraBall : _extraBalls)
    {
        extraBall->update(dt);
	}
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
	AudioMananger::getInstance().playSound("hurt.wav");
    // TODO screen shake.
}

void GameManager::render()
{
    _parralaxBG->draw(*_window);
    _paddle->render();
    _ball->render();
    for (auto& extraBall : _extraBalls)
    {
        extraBall->render();
	}
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _masterText.setString("Level " + std::to_string(_level) + " completed.");
    _levelComplete = true;
}

void GameManager::nextLevel()
{
    _level++;
    _levelComplete = false;
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f, _level);
    _ball->reset();
	_extraBalls.clear();
    _paddle->setWidth(1.0f, 0.0f);
	_countdown = 3.0f;
    
}
void GameManager::addExtraBall()
{
	Ball* extraBall = new Ball(_window, 400.0f, this,sf::Color::Magenta);
	extraBall->setPrimary(false);
	_extraBalls.push_back(extraBall);
}
sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }

Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
