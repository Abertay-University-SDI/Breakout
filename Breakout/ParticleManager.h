#pragma once
#include <vector>
#include "ParticleEffects.h"
#include <SFML/Graphics.hpp>

class GameManager;

class ParticleManager
{
public:
	ParticleManager(sf::RenderWindow* window, GameManager* gameManager);

	void createParticles(sf::Vector2<float> position, float width, float height, sf::Vector2<float> particleSize, int numParticles, int duration);
	void update(float dt);
	void render();

private:
	std::vector<ParticleEffects> _particles;

	sf::RenderWindow* _window;
	GameManager* _gameManager;
};

