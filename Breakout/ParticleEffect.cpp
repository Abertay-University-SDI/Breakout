#include "ParticleEffect.h"
#include <cmath>
#include <cstdlib>

ParticleEffect::ParticleEffect(unsigned int count)
    : m_particles(count), m_shapes(count)
{
    // Initialize with dummy line
    setEmitterLine(sf::Vector2f(300.f, 100.f), sf::Vector2f(500.f, 100.f));
}

void ParticleEffect::setEmitterLine(sf::Vector2f start, sf::Vector2f end) {
    for (std::size_t i = 0; i < m_particles.size(); ++i) {
        float t = static_cast<float>(std::rand()) / RAND_MAX;
        sf::Vector2f emitter = start + t * (end - start);

        Particle& p = m_particles[i];
        p.position = emitter;
        p.velocity = sf::Vector2f(0.f, (std::rand() % 50 + 15)); //Randomising velocity for variations
        p.time = p.initialTime = 1.f;

        sf::RectangleShape& shape = m_shapes[i];
        float size = static_cast<float>(std::rand() % 6 + 4); // Randomising sieze for variations
        shape.setSize(sf::Vector2f(size, size));
        shape.setOrigin(size / 2.f, size / 2.f); // Center the square

        shape.setOrigin(3.f, 3.f);
        shape.setPosition(emitter);
        shape.setFillColor(sf::Color::Red);
    }
}

void ParticleEffect::update() {
    for (std::size_t i = 0; i < m_particles.size(); ++i) {
        Particle& p = m_particles[i];
        p.time -= 0.01f;
        if (p.time < 0.f) p.time = 0.f;

        p.position += p.velocity * 0.01f;

        float alphaRatio = p.time / p.initialTime;
        sf::Uint8 alpha = static_cast<sf::Uint8>(255 * alphaRatio);

        sf::RectangleShape& shape = m_shapes[i];
        shape.setPosition(p.position);
        shape.setFillColor(sf::Color(255, 0, 0, alpha));
    }
}

void ParticleEffect::render(sf::RenderWindow& window) {
    for (const auto& shape : m_shapes)
        window.draw(shape);
}