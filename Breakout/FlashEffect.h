#pragma once
#include "SFML/Graphics.hpp"

class FlashEffect
{
private:
	sf::Sprite flashSprite;
	float alpha = 0.f;
	bool active = false;
	float fadeSpeed = 200.f;

public:
	void showImage(const sf::Texture& texture, sf::Vector2f targetSize, sf::Vector2f centre);
	
	void update(float dt);

	void draw(sf::RenderTarget& target);
};

