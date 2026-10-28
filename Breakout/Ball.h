#pragma once
#include <SFML/Graphics.hpp>

class AudioManager;  // forward declaration
class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setPitchMultiplier(float multiplier) { _pitchMultiplier = multiplier; };

private:
    float _brickBouncePitch;
    float _pitchMultiplier;
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

	AudioManager* _audioManager;  // Reference to the AudioManager
    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

