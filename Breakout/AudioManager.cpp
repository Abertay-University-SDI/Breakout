#include "AudioManager.h"

AudioManager::AudioManager()
{
	soundEffects.push_back(new SoundEffect("Sounds/Bounce.wav", "Bounce"));
}

void AudioManager::playSound(std::string name)
{
	for (int i = 0; i < soundEffects.size(); i++) {
		if (soundEffects[i]->getName() == name) {
			soundEffects[i]->playSound();
		}
	}
}

void AudioManager::adjustPitch(std::string name, float pitch)
{
	for (int i = 0; i < soundEffects.size(); i++) {
		if (soundEffects[i]->getName() == name) {
			soundEffects[i]->setPitch(pitch);
		}
	}
}



// TODO
// add a ball trail
// add scoring and a leaderboard