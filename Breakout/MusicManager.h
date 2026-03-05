#pragma once
#include <SFML/Audio.hpp>

class MusicManager
{ public:

	MusicManager();
	void playBackgroundMusic();
	void playIntenseMusic();
	void updateMusicIntensity(float musicIntensity);

	void update(float dt);

private:

	sf::Music backgroundMusic;
	sf::Music intenseMusic;
	float _MusicIntensity;

	float baseVolume = 40.0f;  // Base volume for background music
	float currentVolume;
};

