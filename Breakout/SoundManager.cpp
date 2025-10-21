#include "SoundManager.hpp"
#include <iostream>

SoundManager::SoundManager()
{
	m_ActiveSounds.reserve(30);
}

SoundManager& SoundManager::Get()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::Play(const std::string& name)
{
	const auto i = m_Sounds.find(name);
	if (i == m_Sounds.end())
		return;

	const auto sound = std::make_shared<sf::Sound>();
	sound->setBuffer(*i->second);
	sound->play();

	m_ActiveSounds.push_back({name, sound});
}

void SoundManager::StopAll() const
{
	for (auto& sound : m_ActiveSounds)
		sound.Sound->stop();
}

void SoundManager::LoadFile(const std::string& name, const std::string& path)
{
	const auto buffer = std::make_shared<sf::SoundBuffer>();
	if (!buffer->loadFromFile(path))
	{
		std::cerr << "Failed to load sound! Path: " << path << '\n';
		return;
	}

	m_Sounds[name] = buffer;
}

bool SoundManager::IsPlaying(const std::string& name) const
{
	for (const auto& [Name, Sound] : m_ActiveSounds)
		if (Name == name && Sound->getStatus() == sf::Sound::Playing)
			return true;

	return false;
}

void SoundManager::Update()
{
	// Removed sounds that finished playing.
	for (auto it = m_ActiveSounds.begin(); it != m_ActiveSounds.end();)
	{
		if (it->Sound->getStatus() == sf::Sound::Stopped)
			it = m_ActiveSounds.erase(it);
		else
			++it;
	}
}
