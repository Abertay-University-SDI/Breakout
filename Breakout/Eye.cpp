#include "Eye.h"

Eye::Eye(float radius, sf::RenderTexture* renderTex, Ball* ball, sf::Color col)
{
	_shapeOuter.setRadius(radius);
	_shapeOuter.setFillColor(sf::Color::White);
	_shapeOuter.setOutlineColor(sf::Color::Black);
	_shapeOuter.setOutlineThickness(5);
	_shapeInner.setFillColor(col);
	_shapeInner.setOutlineColor(sf::Color::Black);
	_shapeInner.setOutlineThickness(3);
	_shapeInner.setRadius(radius * 0.5f);
	_renderTex = renderTex;
	_ball = ball;
}

void Eye::render()
{
	// Get dir to ball
	float outerRadius = _shapeOuter.getRadius();
	sf::Vector2 mid = sf::Vector2(outerRadius, outerRadius);
	sf::Vector2f dir = _ball->getPos() - sf::Vector2f(_shapeOuter.getPosition().x + outerRadius, _shapeOuter.getPosition().y + outerRadius);
	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir = dir / length;
	}
	_shapeInner.setPosition(_shapeOuter.getPosition() + mid * 0.5f + dir * outerRadius * 0.5f);

	_renderTex->draw(_shapeOuter);
	_renderTex->draw(_shapeInner);
}

void Eye::setPos(sf::Vector2f pos)
{
	_shapeOuter.setPosition(pos);
	_shapeInner.setPosition(pos);
}