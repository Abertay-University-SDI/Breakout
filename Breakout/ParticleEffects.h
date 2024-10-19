#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEffects
{
public: 
	ParticleEffects(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles);
	void render(sf::RenderWindow& window);

private:
	std::vector<sf::RectangleShape> particles;
};

