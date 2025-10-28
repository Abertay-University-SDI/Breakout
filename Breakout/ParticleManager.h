#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class ParticleManager
{
public:
    static ParticleManager* getInstance();
    void DrawParticles(sf::RenderWindow* window);

    ParticleManager();
    ~ParticleManager();

private:
    ParticleManager(const ParticleManager&) = delete;
    ParticleManager& operator=(const ParticleManager&) = delete;
    void CreateParticles();

    void TwinkleParticles();


    sf::VertexArray vertices;
    int ParticleCount = 30;
};