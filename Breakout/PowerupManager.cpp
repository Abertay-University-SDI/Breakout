#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball) :
    m_window(window), m_paddle(paddle), m_ball(ball)
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : m_powerups)
    {
        delete powerup;
    }

    m_powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (m_powerupInEffect)
    {
        m_powerupInEffect->second -= dt;

        if (m_powerupInEffect->second <= 0)
        {
            m_powerupInEffect.reset();
        }
    }


    for (auto it = m_powerups.begin(); it != m_powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);

        if (!(*it)->isAlive())
        {
            delete* it;
            it = m_powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : m_powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{

    // TODO finish this.
    switch (rand() % 5)
    {
        case 0:
            m_powerups.push_back(new PowerupBigPaddle(m_window, m_paddle, m_ball));
            break;

        case 1:
            m_powerups.push_back(new PowerupSlowBall(m_window, m_paddle, m_ball));
            break;

        case 2:
            m_powerups.push_back(new PowerupFastBall(m_window, m_paddle, m_ball));
            break;

        case 3:
            m_powerups.push_back(new PowerupSmallPaddle(m_window, m_paddle, m_ball));
            break;

        case 4:
            m_powerups.push_back(new PowerupFireBall(m_window, m_paddle, m_ball));
            break;

        case 5:
           break;
    }

}

void PowerupManager::checkCollision()
{
    for (auto& powerup : m_powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            m_powerupInEffect = powerup->applyEffect();

            powerup->setAlive(false);
        }
    }
}

int PowerupManager::getPowerupsSpawned()
{
    return m_powerups.size();
}

std::pair<POWERUPS, float> PowerupManager::getPowerupInEffect()
{
    if (!m_powerupInEffect) return { none, 0.f };

    return *m_powerupInEffect;
}
