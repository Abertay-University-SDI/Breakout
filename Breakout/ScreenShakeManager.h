#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class ScreenShakeManager {
public:
    ScreenShakeManager(sf::RenderWindow* window);
    void shake(float range, float duration);
    void update(float dt);
    void render();

private:
    const float _shakeSpinSpeed = 50;

    float _shakeTimer = 0;
    float _shakeRangeModifier = 0;
    float _shakeDuration = 0;

    sf::Vector2f _camOffset;
    sf::RenderWindow* _window;
};