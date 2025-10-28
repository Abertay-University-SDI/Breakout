#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    bool isDamaged() const { return _isDamaged; }
    void setDamaged(bool damage) { _isDamaged = damage; }

private:
    sf::RectangleShape _shape;
    sf::Texture _texture;
    sf::Texture _brokenTexture;
    bool _isDamaged;
    bool _isDestroyed;
};