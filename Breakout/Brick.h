#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    int getHealth() const;
    int reduceHealth();
    void nudge(sf::Vector2f amount);
    sf::Vector2f getPosition();

    static sf::Color getColorFromHealth(int health);

private:
    sf::RectangleShape _shape;
    int _health = 3;
    bool _isDestroyed;
};