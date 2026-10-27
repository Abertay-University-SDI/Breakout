#include "FlashEffect.h"
#include <iostream>


void FlashEffect::showImage(const sf::Texture& texture, sf::Vector2f boxSize, sf::Vector2f centre)
{
	flashSprite.setTexture(texture, true);

	sf::Vector2f texSize((float)(texture.getSize().x), (float)(texture.getSize().y));

	flashSprite.setScale({ boxSize.x / texSize.x, boxSize.y / texSize.y });
	flashSprite.setOrigin({ texSize.x / 2.f, texSize.y / 2.f });
	flashSprite.setPosition(centre);
	alpha = 255.f;
	active = true;
	flashSprite.setColor(sf::Color(255, 255, 255, 255));
}

void FlashEffect::update(float dt)
{
	if (!active)
	{
		return;
	}

	alpha -= fadeSpeed * dt;

	if (alpha <= 0.f)
	{
		alpha = 0.f;
		active = false;
	}

	flashSprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)alpha));
}

void FlashEffect::draw(sf::RenderTarget& target)
{
	if (active)
	{
		target.draw(flashSprite);
	}
}