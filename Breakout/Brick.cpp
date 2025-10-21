#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
}

void Brick::render(sf::RenderWindow& window)
{
    if (alpha == 0) {
        return;
    }
    if (!_isDestroyed) {
        window.draw(_shape);
    }
    else {
        elapsedTime += timer.getElapsedTime();
        if (elapsedTime > sf::Time(sf::seconds(0.25)) && alpha > 0) {
            alpha -= 5;
            if (alpha <= 0) alpha = 0;
            _shape.setFillColor(sf::Color(255, 0, 0, alpha));
            timer.restart();
            elapsedTime = sf::Time();
        }
        window.draw(_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}
