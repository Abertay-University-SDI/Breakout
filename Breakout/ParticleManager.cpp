#include "ParticleManager.h"
#include <cstdlib>  // for rand()

static std::unique_ptr<ParticleManager> Instance;

ParticleManager::ParticleManager()
{
}

ParticleManager* ParticleManager::getInstance()
{
    if (!Instance)
    {
        Instance.reset(new ParticleManager());
        Instance->CreateParticles();
    }
    return Instance.get();
}

void ParticleManager::CreateParticles()
{
    vertices.clear();
    int ResizeAmount = ParticleCount * 4;
    vertices.resize(ResizeAmount);
    vertices.setPrimitiveType(sf::Quads);

    for (size_t i = 0; i < ParticleCount; i++)
    {
        int idx = i * 4;
        float OffsetX = static_cast<float>(i + rand() % 1001);
        float OffsetY = static_cast<float>(i + rand() % 1001);

        vertices[idx + 0].position = sf::Vector2f(10.0f + OffsetX, 10.0f + OffsetY);
        vertices[idx + 1].position = sf::Vector2f(20.0f + OffsetX, 10.0f + OffsetY);
        vertices[idx + 2].position = sf::Vector2f(20.0f + OffsetX, 20.0f + OffsetY);
        vertices[idx + 3].position = sf::Vector2f(10.0f + OffsetX, 20.0f + OffsetY);

        vertices[idx + 0].color = sf::Color::White;
        vertices[idx + 1].color = sf::Color::White;
        vertices[idx + 2].color = sf::Color::White;
        vertices[idx + 3].color = sf::Color::White;
    }
}

void ParticleManager::TwinkleParticles()
{
    for (size_t i = 0; i < ParticleCount; i++)
    {
        int idx = i * 4;
        int TwinklA = i + rand() % 10;
        int TwinklB = i + rand() % 10;

        if (TwinklA == TwinklB || TwinklA == TwinklB)
        {
            vertices[idx + 0].color = sf::Color::Black;
            vertices[idx + 1].color = sf::Color::Black;
            vertices[idx + 2].color = sf::Color::Black;
            vertices[idx + 3].color = sf::Color::Black;
        }
        else
        {
            vertices[idx + 0].color = sf::Color::White;
            vertices[idx + 1].color = sf::Color::White;
            vertices[idx + 2].color = sf::Color::White;
            vertices[idx + 3].color = sf::Color::White;
        }
    }
}

void ParticleManager::DrawParticles(sf::RenderWindow* window)
{
    TwinkleParticles();
    window->draw(vertices);
}

ParticleManager::~ParticleManager()
{
    vertices.clear();
}