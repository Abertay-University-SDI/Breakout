#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    if (!_hitBuffer.loadFromFile("Audio/pop.wav"))
        std::cout << "Failed to load hit sound\n";

    _hitSound.setBuffer(_hitBuffer);
}

SoundManager::~SoundManager()
{
}

void SoundManager::playHit()
{
	_timeSinceLastHit = 0.0f;
	_currentPitch += PITCH_STEP;
    if(_currentPitch > PITCH_MAX)
		_currentPitch = PITCH_MAX;

	_hitSound.setPitch(_currentPitch);
    _hitSound.play();
}

void SoundManager::resetPitch()
{
	_currentPitch = PITCH_START;
	_hitSound.setPitch(_currentPitch);
}

void SoundManager::update(float dt)
{
	_timeSinceLastHit += dt;
	if (_timeSinceLastHit >= PITCH_RESET_TIME && _currentPitch != PITCH_START)
	{
		resetPitch();
		_timeSinceLastHit = 0.0f;
	}
}
