#include "ParticleManager.h"

ParticleManager::ParticleManager(sf::RenderWindow* window, GameManager* gameManager)
	: _window(window), _gameManager(gameManager)
{
}

void ParticleManager::createParticles(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles, int duration)
{
	_particles.emplace_back(position, width, height, particleSize, numParticles, duration);
}

void ParticleManager::update(float dt)
{
	for (auto& particle : _particles)
	{
		particle.update(dt);

		if (!particle.toRender)
		{
			particle = _particles.back();
			_particles.pop_back();
		}
	}
}

void ParticleManager::render()
{
	for (auto& particle : _particles)
	{
		particle.render(*_window);
	}
}
