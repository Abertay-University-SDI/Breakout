#include "GameManager.h"
#include <iostream>
#include <random>
#include "Ball.h"
#include "PowerupManager.h"

GameManager::GameManager(sf::RenderWindow* window) : _pause(false),
	_pauseHold(0.f), _time(0.f), _timeLastPowerupSpawned(0.f), _lives(3),
	_levelComplete(false), _powerupInEffect({none, {0.0f, 0.0f}}),
	_window(window),
	_paddle(nullptr), _ball(nullptr), _brickManager(nullptr),
	_powerupManager(nullptr),
	_messagingSystem(nullptr), _ui(nullptr)
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

	// Add sounds.
	SoundManager::Get().LoadFile("bop", "sounds/bop.wav");
	SoundManager::Get().LoadFile("bop2", "sounds/bop2.wav");
	SoundManager::Get().LoadFile("hurt", "sounds/hurt.wav");
	SoundManager::Get().LoadFile("win", "sounds/win.wav");
}

void GameManager::handleMovement(const float dt)
{
	// Keyboard movement.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_paddle->moveRight(dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_paddle->moveLeft(dt);

	// Mouse movement.
	if (!_usingMouse)
		return;
	auto mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*_window));
	float paddleCenter = _paddle->getPosition().x + _paddle->getSize().x / 2.0f;

	if (mousePos.x > paddleCenter)
		_paddle->moveRight(dt);
	if (mousePos.x < paddleCenter)
		_paddle->moveLeft(dt);
}

void GameManager::handleInput(const sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::P)
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
	if (key.code == sf::Keyboard::M)
		_usingMouse = !_usingMouse;
}

void GameManager::update(float dt)
{
	_powerupInEffect = _powerupManager->getPowerupInEffect();
	_ui->updatePowerupBar(_powerupInEffect);
	_powerupInEffect.second.y -= dt;

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
	if (_pauseHold > 0.f)
		_pauseHold -= dt;
	if (_pause)
		return;

	// timer.
	_time += dt;


	if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY &&
		rand() % 700 == 0) // TODO parameterise
	{
		_powerupManager->spawnPowerup();
		_timeLastPowerupSpawned = _time;
	}

	handleMovement(dt);

	// update everything
	_paddle->update(dt);
	_ball->update(dt);
	_powerupManager->update(dt);
	SoundManager::Get().Update();
	updateScreenShake(dt);
}

void GameManager::loseLife()
{
	_lives--;
	_ui->lifeLost(_lives);

	SoundManager::Get().Play("hurt");
	startScreenShake(0.4f, 12.0f);
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
	SoundManager::Get().Play("win");
	_levelComplete = true;
}

void GameManager::startScreenShake(const float duration, const float force)
{
	_isShaking = true;
	_shakeDuration = duration;
	_shakeForce = force;
	_shakeElapsed = 0.0f;
	_originalViewCenter = _window->getView().getCenter();
}

void GameManager::updateScreenShake(const float dt)
{
	if (!_isShaking)
		return;

	_shakeElapsed += dt;
	if (_shakeElapsed < _shakeDuration)
	{
		const float progress = _shakeElapsed / _shakeDuration;
		const float intensity = _shakeForce * (1.0f - progress);

		// Random number generate (-1 - 1).
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution randomVal(-1.0f, 1.0f);

		sf::Vector2f offset;
		offset.x = randomVal(gen) * intensity;
		offset.y = randomVal(gen) * intensity;

		sf::View view = _window->getView();
		view.setCenter(_originalViewCenter + offset);
		_window->setView(view);
	}
	else
	{
		_isShaking = false;
		sf::View view = _window->getView();
		view.setCenter(_originalViewCenter);
		_window->setView(view);
	}
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }

PowerupManager* GameManager::getPowerupManager() const
{
	return _powerupManager;
}
