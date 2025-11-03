#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Eye
{
public:
	Eye(float radius, sf::RenderTexture* renderTex, Ball* ball, sf::Color col = sf::Color::Red);
	void render();
	void setPos(sf::Vector2f pos);


private:
	Ball* _ball;
	sf::RenderWindow* _window;
	sf::RenderTexture* _renderTex;
	sf::CircleShape _shapeOuter;
	sf::CircleShape _shapeInner;
};

