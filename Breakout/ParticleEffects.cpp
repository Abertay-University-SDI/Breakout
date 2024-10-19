#include "ParticleEffects.h"

ParticleEffects::ParticleEffects(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles)
{
	// Add particles to vector
	for (int i = 0; i < numParticles; i++)
	{
		sf::RectangleShape shape;

		// Random position within area
		int randX = rand() % 100;
		int randY = rand() % 100;
		sf::Vector2<float> randPos;
		randPos.x = (width / (float)randX) + (width / 2.f);
		randPos.y = (height / (float)randY) + (height / 2.f);

		// Set sprite details
		shape.setPosition(position.x + randPos.x, position.y + randPos.y);
		shape.setSize(particleSize);
		shape.setFillColor(sf::Color::White);

		// Push particle into vector
		particles.push_back(shape);
	}
}

void ParticleEffects::render(sf::RenderWindow& window)
{
	for (auto& particle : particles)
	{
		window.draw(particle);
	}
}
