#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, int rowCord, int colCord);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2<int> getLocation();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    sf::Vector2<int> _location;

};