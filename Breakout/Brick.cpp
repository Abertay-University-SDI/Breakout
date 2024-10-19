#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Green);
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

int Brick::getHealth() const
{
    return _health;
}

int Brick::reduceHealth()
{
    --_health;

    _shape.setFillColor(getColorFromHealth(_health));

    return _health;
}

void Brick::nudge(sf::Vector2f amount)
{
    _shape.setPosition(_shape.getPosition() + amount);
}

sf::Vector2f Brick::getPosition()
{
    return _shape.getPosition();
}

sf::Color Brick::getColorFromHealth(int health)
{
    switch (health)
    {
        case 2:
            return sf::Color::Yellow;
        case 1:
            return sf::Color::Red;
        default:
            return sf::Color::Green;
    }
}
