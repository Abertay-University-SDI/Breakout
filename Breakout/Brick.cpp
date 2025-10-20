#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, int rowCord, int colCord)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
    _location = sf::Vector2<int>(rowCord, colCord);
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

sf::Vector2<int> Brick::getLocation()
{
    return _location;
}
