#include "AudioManager.h"

AudioManager::AudioManager()
{
	music.setLoop(true);
	music.setVolume(50);
}

AudioManager::~AudioManager()
{
}

void AudioManager::addSound(std::string filename, std::string lname)
{
	sounds.push_back(snd);
	sounds.back().loadSound(filename, lname);
}

void AudioManager::playSoundbyName(std::string lname)
{
	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i].name == lname)
		{
			sounds[i].sound.play();
			return;
		}
	}
}

void AudioManager::stopAllSounds()
{
	for (int i = 0; i < sounds.size(); i++)
	{
		sounds[i].sound.stop();
	}
}

sf::Sound* AudioManager::getSound(std::string lname)
{
	for (int i = 0; i < sounds.size(); i++)
	{
		if (sounds[i].name == lname)
		{
			return &sounds[i].sound;
		}
	}
	return nullptr;
}

void AudioManager::addMusic(std::string filename, std::string lname)
{
	musicTracks.push_back(mu);
	musicTracks.back().setMusic(filename, lname);
}

void AudioManager::playMusicbyName(std::string lname)
{
	for (int i = 0; i < musicTracks.size(); i++)
	{
		if (musicTracks[i].name == lname)
		{
			music.openFromFile(musicTracks[i].filename);
			music.play();
			return;
		}
	}
}

void AudioManager::stopMusic()
{
	music.stop();
}

sf::Music* AudioManager::getMusic()
{
	return &music;
}
