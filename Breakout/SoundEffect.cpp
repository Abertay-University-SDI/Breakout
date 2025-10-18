#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string filepath, std::string soundName)
{
	name = soundName;

	buffer.loadFromFile(filepath);
	sound.setBuffer(buffer);
}

void SoundEffect::playSound()
{
	sound.play();
}

void SoundEffect::setPitch(float pitch)
{
	sound.setPitch(pitch);
}

std::string SoundEffect::getName()
{
	return name;
}
