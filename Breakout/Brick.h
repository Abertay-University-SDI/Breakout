#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    //brick health data
    float _brickHP;
    bool _isDestroyed;

private:
    sf::RectangleShape _shape;
};