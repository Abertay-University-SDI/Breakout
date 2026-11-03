#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
private:
    sf::SoundBuffer _hitBuffer;

    sf::Sound _hitSound;

    float _currentPitch;
	float _timeSinceLastHit;
    static constexpr float PITCH_START = 1.0f;
    static constexpr float PITCH_STEP = 0.1f;
	static constexpr float PITCH_MAX = 2.0f;
	static constexpr float PITCH_RESET_TIME = 1.0f; 
public:
    SoundManager();
    ~SoundManager();

    void playHit();
    void resetPitch();
	void update(float dt);
};
