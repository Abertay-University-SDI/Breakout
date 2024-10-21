#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ParticleEffects
{
public: 
	ParticleEffects(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles, float duration);
	void update(float dt);
	void render(sf::RenderWindow& window);
	float lerp(sf::Color startColour, sf::Color endColour, float time);

	bool toRender = true;

private:
	std::vector<sf::RectangleShape> particles;
	std::vector<sf::Vector2f> directions;
	float timer;
	float totalTime;
	float particleSpeed = 50.f;
};

