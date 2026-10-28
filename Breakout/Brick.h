#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
};