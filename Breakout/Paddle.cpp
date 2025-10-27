#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInPowerup(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));

    _mouseControl = false;
    _velocity = PADDLE_SPEED;
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        if (beastMode)
        {
            _sprite.move(sf::Vector2f(-dt * BEAST_PADDLE_SPEED, 0));
        }

        else
        {
            _sprite.move(sf::Vector2f(-dt * _velocity, 0));
        }
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        if (beastMode)
        {
            _sprite.move(sf::Vector2f(dt * BEAST_PADDLE_SPEED, 0));
        }

        else
        {
            _sprite.move(sf::Vector2f(dt * _velocity, 0));
        }
    }
}

void Paddle::mouseMove(float xPos)
{
    if (xPos < _window->getSize().x - _width && xPos > 0)
    {
        _sprite.setPosition(sf::Vector2f(xPos, _sprite.getPosition().y));
    }
}

void Paddle::update(float dt)
{
    if (_timeInPowerup > 0)
    {
        _timeInPowerup -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
        _velocity = PADDLE_SPEED;   //Reset speed to default
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        if (_mouseControl)
        {
            _mouseControl = false;
        }

        else
        {
            _mouseControl = true;
        }
    }

    if (_mouseControl)
    {
        mouseMove(sf::Mouse::getPosition().x);
    }

}

void Paddle::render()
{
    _window->draw(_sprite);
}

void Paddle::reset()
{
    _sprite.setPosition((_window->getSize().x - _width) / 2.0f, _window->getSize().y - 50.0f);
    beastMode = false;
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    if (beastMode)
    {
        _width = coeff * BEAST_PADDLE_WIDTH;
        _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
        _timeInPowerup = duration;
        float newX = _sprite.getPosition().x + (_width - BEAST_PADDLE_WIDTH) / 2;
        _sprite.setPosition(newX, _sprite.getPosition().y);
    }
    else
    {

        _width = coeff * PADDLE_WIDTH;
        _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
        _timeInPowerup = duration;
        float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
        _sprite.setPosition(newX, _sprite.getPosition().y);
    }
}

void Paddle::setVelocity(float vel, float duration)
{
    _velocity = vel;
    _timeInPowerup = duration;

}
