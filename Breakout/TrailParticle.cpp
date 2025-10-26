#include "TrailParticle.h"
#include "math.h"

TrailParticle::TrailParticle(sf::RenderWindow* _window) : Particle(_window)
{
	sprite.setRadius(10.0f);
	sprite.setFillColor(sf::Color::Blue);
	timeLimit = 1.0f;

}

void TrailParticle::update(const float dt)
{
	Particle::update(dt);

	float alpha{ Math::normalizeRange(0, timeLimit, timer->getElapsedTime().asSeconds()) };

	sprite.setRadius(Math::lerp(10.0f, 0.0f, alpha));
}
