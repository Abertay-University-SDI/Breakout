#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <deque>
#include <iostream>

class ImageManager
{
private:
	std::deque<sf::Texture> displayImages;
	
	mutable std::size_t lastIndex = std::numeric_limits<std::size_t>::max();
public:

	bool loadTexture(const std::string& filename);

	const sf::Texture& getRandomTexture() const;

	std::size_t count() const { return displayImages.size(); }
};

