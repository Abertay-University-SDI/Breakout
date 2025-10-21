#include "Brick.h"

Brick::Brick(float x, float y, float width, float height) :
    m_isDestroyed(false)
{
    m_shape.setPosition(x, y);
    m_shape.setSize(sf::Vector2f(width, height));
    m_shape.setFillColor(sf::Color::Red);
}

void Brick::render(sf::RenderWindow& window)
{
    if (!m_isDestroyed)
    {
        window.draw(m_shape);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return m_shape.getGlobalBounds();
}
