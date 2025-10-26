#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));

    _window = window;
}

Paddle::~Paddle()
{
}

void Paddle::setFreeMove()
{
    _isFreeMove = true;
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

void Paddle::freeMove(float dt)
{
    _sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*_window).x - (PADDLE_WIDTH / 2), sf::Mouse::getPosition(*_window).y));
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }
}

void Paddle::render()
{
    _window->draw(_sprite);
}

float Paddle::getPaddleWidth()
{
    return PADDLE_WIDTH;
}

float Paddle::getPaddleHeight()
{
    return PADDLE_HEIGHT;
}

sf::Vector2f Paddle::getPaddlePos()
{
    //std::cout << "sprite pos: " << sf::Vector2f(_sprite.getPosition()).x << sf::Vector2f(_sprite.getPosition()).y << std::endl;
    return sf::Vector2f(_sprite.getPosition());
}

bool Paddle::getFreeMove()
{
    return _isFreeMove;
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
