#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
class ParralaxBG
{
	struct Layer {
		sf::Texture texture;
		sf::Sprite sprite;
		float factor = 0.f;
		float offset = 0.f;
	};
	std::list<Layer> _layers;
public:
	auto addLayer(const std::string& textureFile, float scrollSpeed) -> void
	{
		Layer& layer = _layers.emplace_back();
		if (!layer.texture.loadFromFile(textureFile))
		{

			_layers.pop_back(),
				throw std::runtime_error("Failed to load texture: " + textureFile);
		}
		layer.texture.setRepeated(true);
		layer.sprite.setTexture(layer.texture);
		layer.factor = scrollSpeed;
	}
	auto update(float playerMoveX, float dt) -> void
	{
		for (auto& layer : _layers)
		{
			layer.offset += playerMoveX * layer.factor;
			float width = static_cast<float>(layer.texture.getSize().x);
			layer.offset = std::fmod(layer.offset, width);
			if (layer.offset < 0.f)
			{
				layer.offset += width;
			}
		}
	}
	auto draw(sf::RenderWindow& window) -> void	
	{
		const sf::Vector2f size(window.getSize());
		for (auto& layer : _layers)
		{
			layer.sprite.setTexture(layer.texture);

			const sf::Vector2f tex(layer.texture.getSize());
			const float scale = size.y / tex.y;
			layer.sprite.setScale(scale, scale);

			layer.sprite.setTextureRect(sf::IntRect(
				static_cast<int>(layer.offset), 0,
				static_cast<int>(size.x / scale),
				static_cast<int>(tex.y)));

			window.draw(layer.sprite);
		}
	}
private:
		sf::Texture _bgTexture;
		sf::Sprite _bgSprite;
		float _scrollSpeed = 0.f;
		float _scrollOffset = 0.f;
};

