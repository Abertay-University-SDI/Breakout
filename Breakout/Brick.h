#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getOrigin() const;
    void damage(float dmg);
    bool isDestroyed();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    int _health = 255;
    
};