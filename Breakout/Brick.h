#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, const sf::Texture* texture, int health);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    int getHealth() const { return _health; }
    void loseHealth(int health) {
        _health -= health; _shape.setFillColor(brickHealthToColor(_health));
    }
    void destroy() { _isDestroyed = true; }
    bool isDestroyed() const { return _isDestroyed; }
private:
    sf::Color brickHealthToColor(int health) const;
    sf::RectangleShape _shape;
    bool _isDestroyed;
    int _health;

};