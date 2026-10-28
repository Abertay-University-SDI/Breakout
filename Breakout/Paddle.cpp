#include "Paddle.h"
#include <iostream>
#include "GameManager.h"

Paddle::Paddle(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true), _gameManager(gameManager)
{
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));


    _sprite1.setFillColor(sf::Color::Cyan);
    _sprite1.setPosition((window->getSize().x + 160) / 2.0f, window->getSize().y - 50.0f);
    _sprite1.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));

    
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
        if (_gameManager->DoubleP == true)
        {
            _sprite1.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
        }
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;
    float position2 = _sprite1.getPosition().x;

    if (_gameManager->DoubleP == true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position2 < _window->getSize().x - 160)
        {
            _sprite1.move(sf::Vector2f(dt * PADDLE_SPEED, 0));

        }
        else if (position2 > _window->getSize().x - 160) {
            return;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }


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
    if (_gameManager->DoubleP == true)
    {
        _window->draw(_sprite1);
    }
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

sf::FloatRect Paddle::getBounds1() const
{
    if (_gameManager->DoubleP == true)
    {
        return _sprite1.getGlobalBounds();
    }
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    if (_gameManager->DoubleP == true)
    {
        _sprite1.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    }
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
