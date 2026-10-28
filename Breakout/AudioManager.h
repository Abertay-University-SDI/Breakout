#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AudioManager
{
public:
	void playSound(float volume, float pitch, std::string filePath);
	void playRandomizedSound(float pitchMin, float pitchMax, std::string filePath);
private:
	sf::SoundBuffer _soundBuffer;
	sf::Sound _sound;
};

