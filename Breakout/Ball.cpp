#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager) :
    m_window(window), m_velocity(velocity), m_gameManager(gameManager),
    m_timeWithPowerupEffect(0.f), m_isFireBall(false), m_isAlive(true), m_direction({1,1})
{
    m_sprite.setRadius(RADIUS);
    m_sprite.setFillColor(sf::Color::Cyan);
    m_sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (m_timeWithPowerupEffect > 0.f)
    {
        m_timeWithPowerupEffect -= dt;
    }
    else
    {
        if (m_velocity != VELOCITY)
        {
            m_velocity = VELOCITY;   // reset speed.
        }
        else
        {
            setFireBall(0);    // disable fireball
            m_sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (m_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        m_sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    m_sprite.move(m_direction * m_velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = m_sprite.getPosition();
    sf::Vector2u windowDimensions = m_window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && m_direction.x > 0) || (position.x <= 0 && m_direction.x < 0))
    {
        m_direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && m_direction.y < 0)
    {
        m_direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        m_sprite.setPosition(0, 300);
        m_direction = { 1, 1 };
        m_gameManager->loseLife();
    }

    // collision with paddle
    if (m_sprite.getGlobalBounds().intersects(m_gameManager->getPaddle()->getBounds()))
    {
        m_direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (m_sprite.getPosition().x - m_gameManager->getPaddle()->getBounds().left) / m_gameManager->getPaddle()->getBounds().width;
        m_direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        m_sprite.setPosition(m_sprite.getPosition().x, m_gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    // collision with bricks
    int collisionResponse = m_gameManager->getBrickManager()->checkCollision(m_sprite, m_direction);

    if (m_isFireBall) return; // no collisisons when in fireBall mode.

    if (collisionResponse == 1)
    {
        m_direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        m_direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    m_window->draw(m_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    m_velocity = coeff * VELOCITY;
    m_timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        m_isFireBall = true;
        m_timeWithPowerupEffect = duration;        
        return;
    }

    m_isFireBall = false;
    m_timeWithPowerupEffect = 0.f;    
}
