#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, bool extralife);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool getIsExtraLife();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    bool _isExtraLife;
};