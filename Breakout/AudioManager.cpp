#include "audioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    if (!buffer.loadFromFile("../audio/sound.wav")) {
        std::cout << "error";
    }
    sound.setBuffer(buffer);
}

void AudioManager::initialize()
{
    
}

void AudioManager::update(float dt)
{
    
}

void AudioManager::playEffect() {
    sound.play();
    sound.setPitch(sound.getPitch() * 1.2);
}
