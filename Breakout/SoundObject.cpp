#include "SoundObject.h"

SoundObject::SoundObject()
{
	buffer = nullptr;
}

SoundObject::~SoundObject()
{
}

void SoundObject::loadSound(std::string filename, std::string lname)
{
	buffer = new sf::SoundBuffer();
	buffer->loadFromFile(filename);
	sound.setBuffer(*buffer);
	name = lname;
}
