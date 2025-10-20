#pragma once
#include "SFML\Audio.hpp"

class SoundObject
{
public:
	SoundObject();
	~SoundObject();

	void loadSound(std::string filename, std::string lname);

	sf::Sound sound;
	std::string name;
private:
	sf::SoundBuffer* buffer;

};