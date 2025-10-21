#pragma once
#include <SFML/Graphics.hpp>


class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setDestroyed(bool destroyed) { _isDestroyed = destroyed; }
    bool getDestroyed() { return _isDestroyed; }
    sf::Uint8 getAlpha() { return alpha; }

private:
    sf::RectangleShape _shape;
    sf::Uint8 alpha = 255;
    sf::Clock timer;
    sf::Time elapsedTime;
    bool _isDestroyed;
};