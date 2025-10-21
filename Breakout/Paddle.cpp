#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window) :
    m_window(window), m_width(PADDLE_WIDTH), m_timeInNewSize(0.0f), m_isAlive(true)
{
    m_sprite.setFillColor(sf::Color::Cyan);
    m_sprite.setPosition((window->getSize().x - m_width) / 2.0f, window->getSize().y - 50.0f);
    m_sprite.setSize(sf::Vector2f(m_width, PADDLE_HEIGHT));
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = m_sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        m_sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = m_sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < m_window->getSize().x - m_width)
    {
        m_sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

void Paddle::update(float dt)
{
    if (m_timeInNewSize > 0)
    {
        m_timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }
}

void Paddle::render()
{
    m_window->draw(m_sprite);
}

sf::FloatRect Paddle::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    m_width = coeff * PADDLE_WIDTH;
    m_sprite.setSize(sf::Vector2f(m_width, m_sprite.getSize().y));
    m_timeInNewSize = duration;
    float newX = m_sprite.getPosition().x + (m_width - PADDLE_WIDTH) / 2;
    m_sprite.setPosition(newX, m_sprite.getPosition().y);
}
