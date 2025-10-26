#pragma once
#include "SFML/Graphics.hpp"

class Particle
{
public:
	Particle(sf::RenderWindow* _window);

	virtual void update(const float dt);
	void render();

	bool getActive() const;

	void setPosition(const sf::Vector2f& position);

protected:
	sf::RenderWindow* window;

	sf::CircleShape sprite;

	bool active{ true };

	std::unique_ptr<sf::Clock> timer{ nullptr };
	float timeLimit{ 0.0f };
};

