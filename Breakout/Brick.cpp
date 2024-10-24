#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, const sf::Texture* texture, int health)
    : _isDestroyed(false), _health(health)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(brickHealthToColor(_health));
    _shape.setTexture(texture);
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

sf::Color Brick::brickHealthToColor(int health) const
{
    switch (health)
    {
    case 1:
        return sf::Color::Red;
        break;
    case 2:
        return sf::Color::Green;
        break;
    case 3:
        return sf::Color::Blue;
        break;
    default:
        return sf::Color::White;
        break;
    }
}