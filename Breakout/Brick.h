#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Brick {
public:
    Brick(float x, float y, float width, float height, int points, int health);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void takeDamage(int damage = 1);
    void setColliding(bool colliding);
    bool getColliding();
    bool getDestroyed();
    int getHealth();
    int getPoints();
private:
    sf::Color calculateColor();
    sf::RectangleShape _shape;
    bool _isDestroyed;
    int _pointValue;
    int _maxHealth;
    int _currentHealth;
    bool _isColliding;
};