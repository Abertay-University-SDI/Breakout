#include "PowerupBase.h"
#include <cmath>
#include <iostream>

PowerupBase::PowerupBase(sf::RenderWindow* window, Paddle* paddle, Ball* ball) :
    m_time(0.0f) // Initialize the time variable
{
    m_window = window;
    m_paddle = paddle;
    m_sprite.setRadius(RADIUS);
    m_isAlive = true;
    m_ball = ball;

    // Initial position and direction with some variability
    float initialX = rand() % window->getSize().x * 0.9 + window->getSize().x * 0.05;
    m_sprite.setPosition(initialX, 5);
    m_direction = { 0.0f, FLOAT_DOWN_SPEED };

}

PowerupBase::~PowerupBase()
{
}

void PowerupBase::update(float dt)
{
    m_time += dt; // Increment time

    // Smooth side-to-side movement using a sine wave
    float sineWave = std::sin(m_time * 2.0f); // Adjust the frequency as needed
    m_direction.x = sineWave * AMPLITUDE_OF_FALL; // Adjust the amplitude as needed

    // Move the power-up
    m_sprite.move(m_direction.x * dt, m_direction.y * dt);

    //// Smooth color changes
    //for (int i = 0; i < _colours.size(); ++i)
    //{
    //    _colours[i] += 50 * dt; // Increment smoothly over time
    //    if (_colours[i] > 255) _colours[i] -= 255; // Wrap around to stay within valid range
    //}
    //_sprite.setFillColor(sf::Color(static_cast<sf::Uint8>(_colours[0]), static_cast<sf::Uint8>(_colours[1]), static_cast<sf::Uint8>(_colours[2]), 255));

    // Collide with floor (i.e., was missed)
    if (m_sprite.getPosition().y + RADIUS * 2 >= m_window->getSize().y)
    {
        m_isAlive = false;
    }

}

void PowerupBase::render()
{
    m_window->draw(m_sprite);
}

bool PowerupBase::checkCollisionWithPaddle()
{
    if (m_sprite.getGlobalBounds().intersects(m_paddle->getBounds()))
    {
        m_isAlive = false;
        return true;
    }

    return false;
}

void PowerupBase::setAlive(bool alive)
{
    m_isAlive = alive;
}

bool PowerupBase::isAlive()
{
    return m_isAlive;
}