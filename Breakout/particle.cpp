#include "Particle.h"

Particle::Particle(sf::RenderWindow* _window)
{
	window = _window;
	timer = std::make_unique<sf::Clock>();
}

void Particle::update(const float dt)
{
	if (timer.get()->getElapsedTime().asSeconds() >= timeLimit)
	{
		active = false;
	}
}

void Particle::render()
{
	if (window)
	{
		window->draw(sprite);
	}
}

bool Particle::getActive() const
{
	return active;
}

void Particle::setPosition(const sf::Vector2f& position)
{
	sf::Vector2f newPosition{ position };
	newPosition.x -= sprite.getRadius();
	newPosition.y -= sprite.getRadius();

	sprite.setPosition(newPosition);
}
