#pragma once
#include <SFML/Audio.hpp>
#include "SoundEffect.h"

class AudioManager
{
public:
	AudioManager();
	void playSound(std::string name);
	void adjustPitch(std::string name, float pitch);

	std::vector<SoundEffect*> soundEffects;
};

