#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEffects
{
public: 
	ParticleEffects(sf::RenderWindow* window, sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles, int duration);
	void update(float dt);
	void render();

private:
	std::vector<sf::RectangleShape> particles;
	float timer;
};

