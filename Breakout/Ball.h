#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Trail.h"


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;
    float _dt;

    Trail* trailManager;
    GameManager* _gameManager;  // Reference to the GameManager

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.

    // ---- Audio ---- //
    sf::SoundBuffer buffer;
    std::vector<sf::Sound>bounce;
};

