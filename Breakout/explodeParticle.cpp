#include "explodeParticle.h"

#include "math.h"

#include <random>

ExplodeParticle::ExplodeParticle(sf::RenderWindow* _window) : Particle(_window)
{
	timeLimit = 0.6f;

	sprite.setRadius(radius);
	sprite.setFillColor(sf::Color::White);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution dis{ -1.0f, 1.0f };

	std::uniform_real_distribution sizeDis{ 0.0f, radiusVariation };

	std::uniform_real_distribution speedDis{ 0.0f, ejectSpeed };

	std::uniform_real_distribution timeDis{ -timeVariation, timeVariation };

	float random{ dis(gen)};

	direction.x = random;

	random = dis(gen);

	direction.y = random;

	radius += sizeDis(gen);
	sprite.setRadius(radius);

	ejectSpeed = speedDis(gen);

	timeLimit += timeDis(gen);
}

void ExplodeParticle::update(const float dt)
{
	Particle::update(dt);

	float alpha{ Math::normalizeRange(0.0f, timeLimit, timer->getElapsedTime().asSeconds()) };

	float newSize{ Math::lerp(radius, 0.0f, alpha) };

	sprite.setRadius(newSize);

	sf::Vector2f position{ sprite.getPosition() };

	position.x += direction.x * ejectSpeed * dt;
	position.y += direction.y * ejectSpeed * dt;

	sprite.setPosition(position);
}

