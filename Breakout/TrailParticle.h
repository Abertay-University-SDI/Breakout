#pragma once
#include "Particle.h"

class TrailParticle : public Particle
{
public:
	TrailParticle(sf::RenderWindow* _window);

	virtual void update(const float dt) override;

};

