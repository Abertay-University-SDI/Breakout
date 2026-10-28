#pragma once
#include <SFML/Graphics.hpp>

class Explosion
{
public:
    Explosion();
    Explosion(float x, float y, float radius);
    void render(sf::RenderWindow& window);
    float getRadius() { return _radius; };
    void setRadius(float r) { _radius = r; };
    sf::Vector2f getCentre() { return _centre; };
    sf::CircleShape getShape() { return _shape; };
    void setExplosion(float x, float y, float r);
    void hide();
private:
    sf::CircleShape _shape;
    float _radius;
    sf::Vector2f _centre;
};


