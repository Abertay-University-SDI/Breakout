#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class AudioManager
{
public:
	AudioManager();
    bool loadSound(const std::string& name, const std::string& filename);
    void playSound(const std::string& name);
	void changePitch(float pitch);
	bool playBackgroundMusic();
	void togglePause();
	void stopMusic();

private:
	std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
	std::unordered_map<std::string, sf::Sound> _sounds;
	sf::Music _backgroundMusic;

	bool _isPaused = false;
};

