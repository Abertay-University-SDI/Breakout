#pragma once

#include "SoundObject.h"
#include "MusicObject.h"
#include "SFML\Audio.hpp"

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	//functions controlling use of sound effect 
	void addSound(std::string filename, std::string lname);
	void playSoundbyName(std::string lname);
	void stopAllSounds();
	sf::Sound* getSound(std::string lname);

	//functions controlling use of music
	void addMusic(std::string filename, std::string lname);
	void playMusicbyName(std::string lname);
	void stopMusic();
	sf::Music* getMusic();

private:
	//list of sounds for use
	std::vector<SoundObject> sounds;
	//lsit of music for use
	std::vector<MusicObject> musicTracks;
	//music object for single stream
	sf::Music music;
	//a sound object that can be reused
	SoundObject snd;
	MusicObject mu;
};