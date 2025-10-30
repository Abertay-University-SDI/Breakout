#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include <vector>

class Trail
{
public:
	Trail(size_t maxLenght = 20, float dotRadius = 2.0f, sf::Color color = sf::Color::White);

	void update(sf::Vector2f position);
	void render(sf::RenderWindow& _window);

	void updateFade();
	void setFillColor(sf::Color color);

private:
	std::vector<sf::CircleShape> _segments;
	size_t _maxLength;
	float _dotRadius;
	sf::Color color;
};

