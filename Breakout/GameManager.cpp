#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window) :
    m_window(window), m_paddle(nullptr), m_ball(nullptr), m_brickManager(nullptr), m_powerupManager(nullptr),
    m_messagingSystem(nullptr), m_ui(nullptr), m_pause(false), m_time(0.f), m_lives(3), m_pauseHold(0.f), m_levelComplete(false),
    m_powerupInEffect({ none,0.f }), m_timeLastPowerupSpawned(0.f)
{
    m_font.loadFromFile("font/montS.ttf");
    m_masterText.setFont(m_font);
    m_masterText.setPosition(50, 400);
    m_masterText.setCharacterSize(48);
    m_masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    m_paddle = new Paddle(m_window);
    m_brickManager = new BrickManager(m_window, this);
    m_messagingSystem = new MessagingSystem(m_window);
    m_ball = new Ball(m_window, 400.0f, this); 
    m_powerupManager = new PowerupManager(m_window, m_paddle, m_ball);
    m_ui = new UI(m_window, m_lives, this);

    // Create bricks
    m_brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    m_powerupInEffect = m_powerupManager->getPowerupInEffect();
    m_ui->updatePowerupText(m_powerupInEffect);
    m_powerupInEffect.second -= dt;
    

    if (m_lives <= 0)
    {
        m_masterText.setString("GAME OVER");
        return;
    }

    if (m_levelComplete)
    {
        m_masterText.setString("LEVEL COMPLETED");
        return;
    }

    // pause and pause handling
    if (m_pauseHold > 0.f) m_pauseHold -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        if (!m_pause && m_pauseHold <= 0.f)
        {
            m_pause = true;
            m_masterText.setString("PAUSED");
            m_pauseHold = PAUSE_TIME_BUFFER;
        }

        if (m_pause && m_pauseHold <= 0.f)
        {
            m_pause = false;
            m_masterText.setString("");
            m_pauseHold = PAUSE_TIME_BUFFER;
        }
    }

    if (m_pause)
    {
        return;
    }

    // timer.
    m_time += dt;


    if (m_time > m_timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        m_powerupManager->spawnPowerup();
        m_timeLastPowerupSpawned = m_time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) m_paddle->moveLeft(dt);

    // update everything 
    m_paddle->update(dt);
    m_ball->update(dt);
    m_powerupManager->update(dt);
}

void GameManager::loseLife()
{
    m_lives--;
    m_ui->lifeLost(m_lives);

    // TODO screen shake.
}

void GameManager::render()
{
    m_paddle->render();
    m_ball->render();
    m_brickManager->render();
    m_powerupManager->render();
    m_window->draw(m_masterText);
    m_ui->render();
}

void GameManager::levelComplete()
{
    m_levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return m_window; }

UI* GameManager::getUI() const { return m_ui; }

Paddle* GameManager::getPaddle() const { return m_paddle; }

BrickManager* GameManager::getBrickManager() const { return m_brickManager; }

PowerupManager* GameManager::getPowerupManager() const { return m_powerupManager; }
