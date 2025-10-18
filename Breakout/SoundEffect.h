#pragma once
#include <SFML/Audio.hpp>

class SoundEffect
{
public:
	SoundEffect(std::string filepath, std::string soundName);
	
	void playSound();

	void setPitch(float pitch);

	std::string getName();

private:
	std::string name;
	sf::Sound sound;
	sf::SoundBuffer buffer;
};

