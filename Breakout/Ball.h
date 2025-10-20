#pragma once
#include <SFML/Graphics.hpp>
#include "POWERUPS.h"

class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void resetBall();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setPowerup(float duration, POWERUPS newpowerup);
    POWERUPS getPowerup();

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    float _respawnHold;
    float _respawnBlinkTimer;
    bool _isAlive;
    bool _isFireBall;
    bool _isBallRespawning;
    float _timeWithPowerupEffect;
    POWERUPS _currentPowerup;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
    static constexpr float RESPAWN_TIME_DELAY = 1.0f; //How long it takes for the ball to respawn
    static constexpr float RESPAWN_BLINK_ON_DURATION = 0.5f; //how long a respawn blink lasts
    static constexpr float RESPAWN_BLINK_OFF_DURATION = 0.25f; //how long a respawn blink is off for before it blinks on
};

