#include "ImageManager.h"
#include <random>
#include <stdexcept>


bool ImageManager::loadTexture(const std::string& filename)
{
	sf::Texture displayTexture;
	if (!displayTexture.loadFromFile(filename))
	{
		std::cerr << "Failed to load texture: " << filename << "\n";
		return false;
	}

	displayTexture.setSmooth(true);
	displayImages.push_back(std::move(displayTexture));
	return true;
}

const sf::Texture& ImageManager::getRandomTexture() const
{
	if (displayImages.size() == 1)
	{
		lastIndex = 0;
		return displayImages[0];
	}

	static std::mt19937 generate{ std::random_device{}() };

	std::uniform_int_distribution<std::size_t> dist(0, displayImages.size() - 2);

	std::size_t index = dist(generate);

	if (index >= lastIndex)
	{
		++index;
	}

	lastIndex = index;
	return displayImages[index];
}
