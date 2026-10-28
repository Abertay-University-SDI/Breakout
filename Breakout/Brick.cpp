#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, int hitPoints)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
	_hitPoints = hitPoints;
	
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        _color = sf::Color::Red;
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::hit()
{
	_hitPoints--;
}

int Brick::getHitPoints() const
{
    return _hitPoints;
}


