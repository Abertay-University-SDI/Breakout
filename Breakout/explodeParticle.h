#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"


class ExplodeParticle : public Particle
{
public:
	ExplodeParticle(sf::RenderWindow* _window);

	virtual void update(const float dt) override;

	

	

private:


	float timeVariation{ 0.2f };

	float radius{ 10.0f };
	float radiusVariation{ 5.0f };


	sf::Vector2f direction;
	float ejectSpeed{ 100.0f };

	
};

