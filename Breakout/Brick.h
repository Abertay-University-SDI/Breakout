#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, float starting_health);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    void update_hit_time(float time);

    void decrease_health();
    float get_health();

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    float health, hit_time = 0, hit_time_max = 0.1;

    void update_colour();
};