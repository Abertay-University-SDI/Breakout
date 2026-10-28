#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>
#include <iostream>
class AudioMananger
{
	sf::SoundBuffer _buffer;
	sf::Music _music;
	std::unordered_map<std::string, sf::SoundBuffer> _soundBuffers;
	std::unordered_map<std::string, sf::Sound> _sounds;
	AudioMananger() {
		/*std::cout << "Working dir: " << std::filesystem::current_path() << '\n';*/
	/*	std::cout << std::filesystem::exists("assets/sounds/hurt_4.wav") << '\n';*/
		_music.openFromFile("../assets/sounds/alex-morgan-synthwave-music-neon-drive-horizon-578508.ogg");
		_music.setLoop(true);
		_music.setVolume(10.f);
		_music.play();
	}
	AudioMananger(const AudioMananger&) = delete;
public:
	static auto getInstance() -> AudioMananger&
	{
		static AudioMananger instance;
		return instance;
	}

	auto loadSoundBuffer(std::string sound) -> bool {

		if (_soundBuffers.count(sound)) {
			return true;
		}
		if (!_soundBuffers[sound].loadFromFile("../assets/sounds/" + sound)) {
			_soundBuffers.erase(sound);
			return false;
		}
		_sounds[sound].setBuffer(_soundBuffers[sound]);
		return true;
	}
	auto playSound(const std::string& sound) -> void {
		/*std::cout << "playSound called: " << sound << '\n';*/
		if (!loadSoundBuffer(sound)) {
			std::cout << "  load failed: " << sound << '\n';
			return;
		}

		sf::Sound& localSound = _sounds[sound];
		if (localSound.getBuffer() != &_soundBuffers[sound])
			localSound.setBuffer(_soundBuffers[sound]);

		localSound.setVolume(20.f);
		localSound.play();
		/*std::cout << "playing " << sound << ", status " << localSound.getStatus() << '\n';*/
	}


};

