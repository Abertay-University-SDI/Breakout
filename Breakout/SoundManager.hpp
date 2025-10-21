#pragma once
#include <map>
#include "SFML/Audio.hpp"

struct ActiveSound
{
	std::string Name;
	std::shared_ptr<sf::Sound> Sound;
};


class SoundManager
{
public:
	static SoundManager& Get();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	SoundManager(SoundManager&&) = delete;
	SoundManager& operator=(SoundManager&&) = delete;


	void Play(const std::string& name);
	void StopAll() const;

	void LoadFile(const std::string& name, const std::string& path);

	bool IsPlaying(const std::string& name) const;

	void Update();

private:
	SoundManager();

private:
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> m_Sounds{};
	std::vector<ActiveSound> m_ActiveSounds{};
};
