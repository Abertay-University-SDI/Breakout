#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window, bool cont)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    controls = cont;

}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this, true); 
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


    // move paddle
    if (controls == true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);
    }
    else
    {
        _paddle->followMouse();
    }    

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    for (auto* temp : _secondaryBalls) { temp->update(dt); }
    _powerupManager->update(dt);

    if (shake)
    {
        shakeTime += dt;
        //stop shake after given time
        if (shakeTime > shakeEndTime)
        {
            //unshake last
            _paddle->shake(-randShake);
            _ball->shake(-randShake);
            for (auto* temp : _secondaryBalls) { temp->shake(-randShake); }
            _brickManager->shake(-randShake);

            //reset variables
            shake = false;
            randShake = 0;
            shakeTime = 0;
            lastShake = 0;
        }

        //shake based on 
        if (shake && shakeTime > shakeIntervals + lastShake)
        {
            //unshake last
            _paddle->shake(-randShake);
            _ball->shake(-randShake);
            for (auto* temp : _secondaryBalls) { temp->shake(-randShake); }
            _brickManager->shake(-randShake);

            //shake
            lastShake = shakeTime;
            randShake = (rand() % shakeIntensity) - (shakeIntensity / 2);
            _paddle->shake(randShake);
            _ball->shake(randShake);
            for (auto* temp : _secondaryBalls) { temp->shake(-randShake); }
            _brickManager->shake(randShake);
        }
    }
    
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    // TODO screen shake. [DONE]
    shake = true;
}

void GameManager::render()
{    
    _paddle->render();
    _ball->render();
    for (auto* temp : _secondaryBalls) { temp->render(); }
    _brickManager->render();
    _powerupManager->render();
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


void GameManager::createSecondaryBall()
{
    _secondaryBalls.emplace_back(new Ball(_window, 400.0f, this, false));
}

void GameManager::deleteSecondaryBall(Ball* ball)
{
    for (int i = 0; i < _secondaryBalls.size(); i++)
    {
        if (_secondaryBalls.at(i) == ball)
        {
            _secondaryBalls.erase(_secondaryBalls.begin() + i);
        }
    }
}