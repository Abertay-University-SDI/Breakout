#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    loadSound("powerup_collect", "Resources/Sounds/collect.wav");
    loadSound("brick_break", "Resources/Sounds/pop.wav");
    loadSound("paddle_hit", "Resources/Sounds/electric_boop.wav");
    loadSound("game_over", "Resources/Sounds/game_over.wav");
    loadSound("life_lost", "Resources/Sounds/life_lost.wav");
    loadSound("wall_hit", "Resources/Sounds/wall_hit.wav");
}

// Load a sound effect with an ID into maps.
bool AudioManager::loadSound(const std::string& name, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Failed to load sound: " << filename << std::endl;
        return false;
    }

    _soundBuffers[name] = buffer;
    _sounds[name].setBuffer(_soundBuffers[name]);
    return true;
}

// Plays a sound effect using an ID.
void AudioManager::playSound(const std::string& name) {
    auto it = _sounds.find(name);
    if (it != _sounds.end()) {
        it->second.play();
    }
    else {
        std::cerr << "Sound not found: " << name << std::endl;
    }
}

// Change the pitch (speed) of all audio.
void AudioManager::changePitch(float pitch) 
{
    for (auto& [name, sound] : _sounds) {
        sound.setPitch(pitch);
    }

    _backgroundMusic.setPitch(pitch);
}

// Play the background music
bool AudioManager::playBackgroundMusic()
{
    if (!_backgroundMusic.openFromFile("Resources/Sounds/bgm.wav")) {
        std::cerr << "Failed to load background music " << std::endl;
        return false;
    }

    _backgroundMusic.setVolume(50.f);
    _backgroundMusic.setLoop(true);
    _backgroundMusic.play();
    return true;
}

// Toggles play on all currently active audio.
void AudioManager::togglePause()
{
    if (_isPaused) {
        // Resume all paused sounds
        for (auto& [name, sound] : _sounds) {
            if (sound.getStatus() == sf::Sound::Paused) {
                sound.play();
            }
        }

        if (_backgroundMusic.getStatus() == sf::Music::Paused) {
            _backgroundMusic.play();
        }

        _isPaused = false;
    }
    else {
        // Pause all currently playing sounds
        for (auto& [name, sound] : _sounds) {
            if (sound.getStatus() == sf::Sound::Playing) {
                sound.pause();
            }
        }

        if (_backgroundMusic.getStatus() == sf::Music::Playing) {
            _backgroundMusic.pause();
        }

        _isPaused = true;
    }
}

// Stops the background music.
void AudioManager::stopMusic() 
{
    _backgroundMusic.stop();
}
