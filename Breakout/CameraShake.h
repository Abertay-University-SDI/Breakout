#pragma once
#include <SFML/Graphics.hpp>
#include <random>
class CameraShake
{
public:
	CameraShake(sf::RenderWindow* window) : _window(window) {};

    void startScreenShake(float shakeDur, float shakeStr);
    void Update(float dt);

private:

    float shakeDuration = 0.0f;
    float shakeStrength = 0.0f;
    sf::RenderWindow* _window;

    //Do the randomising
    std::default_random_engine randomiser;
    std::uniform_real_distribution<float> distributor{ -1.f, 1.f };
};

