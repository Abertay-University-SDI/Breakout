#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    void setIsDestroyed(bool b) { _isDestroyed = b; }
    bool isDestroyed() { return _isDestroyed; }

private:
    sf::RectangleShape _shape;
    bool _isDestroyed = false;
};