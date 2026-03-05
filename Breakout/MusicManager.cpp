#include "MusicManager.h"
#include <iostream>

MusicManager::MusicManager()
{
    if (!backgroundMusic.openFromFile("audio/background_music.wav")) {
        std::cerr << "Failed to load background music!" << std::endl;
    }
    if (!intenseMusic.openFromFile("audio/intense_music.wav")) {
        std::cerr << "Failed to load intense music!" << std::endl;
    }
    backgroundMusic.setLoop(true);
    intenseMusic.setLoop(true);
    backgroundMusic.setVolume(40.0f);
    intenseMusic.setVolume(100.0f);
}

void MusicManager::playBackgroundMusic()
{
    backgroundMusic.setVolume(100.0f);
    backgroundMusic.play();
}

void MusicManager::updateMusicIntensity(float musicIntensity)
{
    backgroundMusic.setVolume(baseVolume + musicIntensity);
}

// Optional: Call this from your main update loop for fade-out support
void MusicManager::update(float dt)
{

}
