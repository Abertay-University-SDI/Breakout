#include "PowerupBase.h"
#include <cmath>
#include <iostream>

PowerupBase::PowerupBase(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _time(0.0f) 
{
    _window = window;
    _paddle = paddle;
    _sprite.setRadius(RADIUS);
    _isAlive = true;
    _ball = ball;

    // Initial position and direction with some variability
    float initialX = rand() % window->getSize().x * 0.9 + window->getSize().x * 0.05;
    _sprite.setPosition(initialX, 5);
    _direction = { 0.0f, FLOAT_DOWN_SPEED };

}

PowerupBase::~PowerupBase()
{
}

void PowerupBase::update(float dt)
{
    //Increment time
    _time += dt;

    // Smooth side-to-side movement using a sine wave
    float sineWave = std::sin(_time * 2.0f); 
    _direction.x = sineWave * AMPLITUDE_OF_FALL;

    // Move the power-up
    _sprite.move(_direction.x * dt, _direction.y * dt);

    if (_sprite.getPosition().y + RADIUS * 2 >= _window->getSize().y)
    {
        _isAlive = false;
    }

}

void PowerupBase::render()
{
    _window->draw(_sprite);
}

bool PowerupBase::checkCollisionWithPaddle()
{
    if (_sprite.getGlobalBounds().intersects(_paddle->getBounds()))
    {
        _isAlive = false;
        return true;
    }
    return false;
}

void PowerupBase::setAlive(bool alive)
{
    _isAlive = alive;
}

bool PowerupBase::isAlive()
{
    return _isAlive;
}