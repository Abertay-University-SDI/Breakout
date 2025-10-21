#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

class ScreenShake {
public:
    void trigger(float amplitudePixels, float durationSec, float frequencyHz = 20.f) {
        _amp = amplitudePixels; // max pixel offset at start
        _dur = durationSec; // how long shake lasts
        _time = 0.f; // reset time elapsed
        _freq = frequencyHz; //how fast it oscillates

        //random seeds so shakes dont look identical
        _seedX = rand01();
        _seedY = rand01();
        _active = true;
    }

    void update(float dt) {
        //no shake is playing
        if (!_active) { _offset = { 0.f, 0.f }; return; }

        //ends the shake when duration is reached
        _time += dt;
        if (_time >= _dur) { _active = false; _offset = { 0.f, 0.f }; return; }

        // quadratic decay - amplitude smoothly decays from 1 -> 0 using a quadratic curve (t^2)
        float t = 1.f - (_time / _dur);
        float amp = _amp * t * t;

        // generates two oscillators (sine and cosine) at the chosen frequency
        const double pi = std::acos(-1);
        float x = std::sin((_time + _seedX) * _freq * (30 * 2));
        float y = std::cos((_time + _seedY) * _freq * (30 * 2));

        //scales the oscillators by current amplitude to get the pixel offset
        _offset = { x * amp, y * amp };
    }

    // add to camera center each frame
    sf::Vector2f offset() const { return _offset; }

    // logic on whether a shake is running
    bool active() const { return _active; }

private:
    //random number generator 1
    static float rand01() {
        return static_cast<float>(std::rand()) / RAND_MAX;
    }

    //initialisations
    float _amp = 0.f, _dur = 0.f, _time = 0.f, _freq = 20.f;
    float _seedX = 0.f, _seedY = 0.f;
    bool _active = false;
    sf::Vector2f _offset{ 0.f, 0.f };
};
