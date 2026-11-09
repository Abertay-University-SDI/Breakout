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

    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
	// check for game over or level complete
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

    // Pause Menu
    if (_pauseHold > 0.f) 
        _pauseHold -= dt;

	// toggle pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && _pauseHold <= 0.f)
    {
        _pause = !_pause;
        _pauseHold = PAUSE_TIME_BUFFER;

        if (_pause)
            _ui->resetPauseMenu();
    }

    if (_pause)
    {
		updatePauseMenu();
        return;
    }

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
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();

    if (_pause)
		_ui->renderPauseMenu();
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

// Pause Menu controls and logic
void GameManager::updatePauseMenu()
{
	// Handle pause menu input and update selected option
	const bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	const bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	const bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
	const bool click = sf::Mouse::isButtonPressed(sf::Mouse::Left);

    bool activate = false;

    //Keyboard controls
    if (up && !lastUp)
        _ui->updatePauseOption(-1);
    if (down && !lastDown)
		_ui->updatePauseOption(1);
    if (enter && !lastEnter)
		activate = true;

	//Mouse controls
	const sf::Vector2i mousePos = sf::Mouse::getPosition(*_window); 
	const int mouseHover = _ui->getPauseAt(_window->mapPixelToCoords(mousePos));

    if (mouseHover >= 0)
    {
        if (mousePos != lastMousePos)
			_ui->setPauseOption(mouseHover);
        if (click && !lastClick) {

			_ui->setPauseOption(mouseHover);
			activate = true;
        }
    }

	lastUp = up; lastDown = down; lastEnter = enter;
	lastClick = click; lastMousePos = mousePos;

    if (activate)
        setPauseOption();
}

// Handle the selected pause option
void GameManager::setPauseOption()
{
    switch (_ui->getPauseOption())
    {
    case PauseOptions::RESUME:
        _pause = false;
		_pauseHold = PAUSE_TIME_BUFFER;
        break;
    case PauseOptions::RESTART:
        restart();
        break;
    case PauseOptions::EXIT:
        _window->close();
        break;
    default:
        break;
    }
}

// Restart the game 
void GameManager::restart()
{
	//Delete existing objects
    delete _paddle;
    delete _ball;
    delete _brickManager;
    delete _powerupManager;
    delete _messagingSystem;
	delete _ui;

	//Reset game state
    _pause = false;
    _time = 0.f;
    _lives = 3;
    _pauseHold = 0.f;
    _levelComplete = false;
    _powerupInEffect = { none,0.f };
	_timeLastPowerupSpawned = 0.f;

	initialize();
}