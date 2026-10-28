#include "AudioManager.h"

void AudioManager::playSound(float volume, float pitch, std::string filePath)
{
	_soundBuffer.loadFromFile(filePath);
	_sound.setBuffer(_soundBuffer);
	_sound.setVolume(volume);
	_sound.setPitch(pitch);
	_sound.play();
}

void AudioManager::playRandomizedSound(float pitchMin, float pitchMax, std::string filePath)
{
	float randomPitch = pitchMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (pitchMax - pitchMin)));
	playSound(100.0f, randomPitch, filePath);
}