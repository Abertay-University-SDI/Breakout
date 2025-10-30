#include "Trail.h"


Trail::Trail(size_t maxLength, float dotRadius, sf::Color color) 
	: _maxLength(maxLength), _dotRadius(dotRadius), color(color) {
}


void Trail::update(sf::Vector2f position) {
	sf::CircleShape dot(_dotRadius);
	dot.setOrigin(_dotRadius, _dotRadius);
	dot.setPosition(position);
	dot.setFillColor(color);
	_segments.push_back(dot);

	if (_segments.size() > _maxLength) {
		_segments.erase(_segments.begin());
	}
}

void Trail::render(sf::RenderWindow& _window) {
	const size_t count = _segments.size();
	for (int i = 0; i < count; i++)
	{
		float t = static_cast<float>(i) / count; 
		t = t * t;

		//Fade
		sf::Color faded = color;

		//Created the fade based on the current segment
		faded.a =  25.5f * t;

		float radius = _dotRadius * t;
		sf::CircleShape dot(radius);
		dot.setOrigin(radius, radius);
		dot.setPosition(_segments[i].getPosition());
		//Apply the aplha
		dot.setFillColor(faded);

		_window.draw(dot, sf::RenderStates(sf::BlendAlpha));

	}
}

void Trail::setFillColor(sf::Color newColor) {
	color = newColor;
}
