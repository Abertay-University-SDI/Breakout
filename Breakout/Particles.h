#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"

// Liquid drops. The shader melts nearby drops together with a smooth min, so a splash
// reads as one blob of liquid rather than separate balls.
class Particles
{
public:
    Particles(sf::RenderWindow* window, Paddle* paddle);

    void splash(sf::Vector2f position, sf::Color colour, int count);
    void update(float dt);
    void render();

private:
    struct Drop
    {
        sf::Vector2f position;
        sf::Vector2f velocity;
        float radius;
        float life;
        float maxLife;
        sf::Color colour;
    };

    sf::RenderWindow* _window;
    Paddle* _paddle;
    std::vector<Drop> _drops;

    static constexpr size_t MAX_DROPS = 48;        // matches MAX_PARTICLES in the shader
    static constexpr float GRAVITY = 900.0f;
    static constexpr float DRAG = 1.5f;            // velocity lost per second, as a fraction
    static constexpr float SPLASH_ANGLE = 1.2f;    // max launch angle either side of straight up (radians, ~70 degrees)
    static constexpr float COHESION = 7.0f;        // pull between nearby drops
    static constexpr float COHESION_RANGE = 40.0f;
    static constexpr float SEPARATION = 120.0f;    // push between overlapping drops
    static constexpr float BOUNCE = 0.3f;          // velocity kept when hitting the paddle or walls
};
