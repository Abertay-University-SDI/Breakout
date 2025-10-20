#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

GameManager::GameManager(sf::RenderWindow* window, AudioManager* audioManager)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);

    audio = audioManager;

    audio->addMusic("sfx/BackgroundMusic.wav","music");
    audio->addSound("sfx/beep.ogg", "beep");
    audio->addSound("sfx/break.ogg", "break");
    audio->addSound("sfx/damage.ogg", "damage");

    audio->getSound("break")->setVolume(20);
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
    
    if (audio->getMusic()->getStatus() == sf::SoundSource::Stopped)
    {
        audio->playMusicbyName("music");
    }

    if (_lives <= 0)
    {
        _masterText.setString("Game over. Press enter to Exit");
        audio->stopMusic();
        audio->stopAllSounds();
        return;        
        
    }
    if (_levelComplete)
    {  

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


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%spawnChance == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    //for shaking camera
    if (shaking)
    {
        sf::View view = _window->getView();
        if (shakeDuration > 0)
        {
            float offsetX = rand() % shakeX;
            float offsetY = rand() % shakeY;

           
            view.setCenter(originalViewX + offsetX, originalViewY + offsetY);
            _window->setView(view);

            shakeDuration -= shakeFade * dt;
            
        }
        else
        {
            shaking = false;
            view.setCenter(originalViewX, originalViewY);
            _window->setView(view);
        }
    }

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);
    audio->playSoundbyName("damage");
    shakeCamera(2, 50,50,5);
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
    _levelComplete = true;
}

void GameManager::shakeCamera(float duration, int x, int y, float fade)
{
    shaking = true;
    shakeDuration = duration;
    shakeX = x;
    shakeY = y;
    shakeFade = fade;
    originalViewX = _window->getView().getCenter().x;
    originalViewY = _window->getView().getCenter().y;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
