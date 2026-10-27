#pragma once
#include <SFML/Graphics.hpp>

// Draws the game's shapes as 3D ray marched objects (see shaders/raymarch.frag).
// Objects call add() from their render() instead of window.draw(); draw() then renders
// everything added this frame in one fullscreen pass.
namespace Raymarch
{
    bool init();
    void add(const sf::RectangleShape& box);
    void add(const sf::CircleShape& sphere);
    // Liquid drop: drops smoothly melt into each other and into nearby shapes.
    void addParticle(sf::Vector2f position, float radius, sf::Color colour);
    void draw(sf::RenderWindow& window);
}
