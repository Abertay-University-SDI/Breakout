#include "Explosion.h"

Explosion::Explosion()
{
    _shape.setPosition(0,0);
    _shape.setRadius(1);
    _shape.setOutlineColor(sf::Color::Blue);
    _shape.setOutlineThickness(0.f);
    _shape.setFillColor(sf::Color::Transparent);
    _centre = sf::Vector2f{ 0,0 };
}

Explosion::Explosion(float x, float y, float radius)
{
    _shape.setPosition(x, y);
    _shape.setRadius(radius);
    _shape.setOutlineColor(sf::Color::Blue);
    _shape.setOutlineThickness(0.f);
    _centre = sf::Vector2f{ x,y };
}

void Explosion::render(sf::RenderWindow& window)
{
   
  window.draw(_shape);
    
}

void Explosion::setExplosion(float x, float y, float r)
{
    _shape.setPosition(x - r, y - r);
    _shape.setRadius(r);
    _shape.setOutlineThickness(10.f);
    _centre = sf::Vector2f{ x ,y  };
    _radius = r;
   
}

void Explosion::hide()
{
    _shape.setOutlineThickness(0.f);
    _shape.setPosition(0, 0);
    _centre = sf::Vector2f(0, 0);
}

