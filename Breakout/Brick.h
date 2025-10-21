#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Brick {
public:
    Brick(float x, float y, float width, float height, bool hasEyes = false, bool isBoss = false, int health = 1);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setEyes(bool hasEyes);
    void setDestroyed(bool isDestroyed);
    bool isDestroyed() const;
    bool hasEyes() const;
    bool isBoss() const;
    void takeDamage();
    void update(float dt);
    int getHealth() const; 

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    bool _hasEyes;
    int _bossHealth;
    bool _isBoss;
    sf::Vector2f _bossVelocity;
    float _hitColorTimer; 
};