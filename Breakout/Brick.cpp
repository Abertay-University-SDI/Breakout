#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, bool extralife)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
    _isExtraLife = extralife;
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

bool Brick::getIsExtraLife()
{
    return _isExtraLife;
}
