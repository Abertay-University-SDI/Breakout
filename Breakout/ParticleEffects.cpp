#include "ParticleEffects.h"

ParticleEffects::ParticleEffects(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles, int duration)
{
	// Add particles to vector
	for (int i = 0; i < numParticles; i++)
	{
		sf::RectangleShape shape;

		// Calculate direction of each particle
		sf::Vector2f direction;
		direction.x = (float)(rand() % 200) / 100.f - 1;
		direction.y = (float)(rand() % 200) / 100.f - 1;
		directions.push_back(direction);


		// Set sprite details
		shape.setPosition(position.x + width / 2.f - particleSize.x / 2.f, position.y + height / 2.f - particleSize.y / 2.f);
		shape.setSize(particleSize);
		shape.setFillColor(sf::Color::White);

		// Push particle into vector
		particles.push_back(shape);
	}

	timer = duration;
}

void ParticleEffects::update(float dt)
{
	timer -= dt;

	// Particle Animation
	if (toRender)
	{
		int count = 0;
		for (auto& particle : particles)
		{
			particle.move(sf::Vector2f(particleSpeed * directions[count].x, particleSpeed * directions[count].y) * dt);
			count++;
		}
	}

	// Stop render after time expires
	if (timer <= 0)
	{
		toRender = false;
	}
}

void ParticleEffects::render(sf::RenderWindow& window)
{
	if (toRender)
	{
		for (auto& particle : particles)
		{
			window.draw(particle);
		}
	}
}
