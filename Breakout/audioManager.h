#pragma once
#include<SFML/Audio.hpp>

class AudioManager {
public:
    AudioManager();
    void initialize();
    void update(float dt);
    void playEffect();

   
    sf::SoundBuffer buffer;
    sf::Sound sound;

private:
   
};
