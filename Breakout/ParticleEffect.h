#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float time;
    float initialTime;
};

class ParticleEffect {
public:
    ParticleEffect(unsigned int count);

    void setEmitterLine(sf::Vector2f start, sf::Vector2f end);
    void update();
    void render(sf::RenderWindow& window);

private:
    std::vector<Particle> m_particles;
    std::vector<sf::RectangleShape> m_shapes;
};
