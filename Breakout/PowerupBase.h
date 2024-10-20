#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

// Bugfix: PowerupFireball class attempting to inherit from a class which doesn't exist yet (PowerupBase), do not need to include this header as no dependancies exist within this class
// that rely on anything within the PowerupFireball header file.
//#include "PowerupFireBall.h"


class PowerupBase
{
public:
    PowerupBase(sf::RenderWindow* window, Paddle* paddle, Ball* ball);
    virtual ~PowerupBase();

    void update(float dt);
    void render();

    virtual std::pair<POWERUPS, float> applyEffect() = 0; // Pure virtual method for applying the power-up effect
    bool checkCollisionWithPaddle();

    void setAlive(bool alive);
    bool isAlive();

protected: // Protected so derived classes can access these members
    // Constants
    static constexpr float RADIUS = 20.f;               // size of powerup on screen
    static constexpr float FLOAT_DOWN_SPEED = 250.0f;   // speed of fall
    static constexpr float AMPLITUDE_OF_FALL = 80.0f;   // waviness of fall

    // Game logic
    float _time;
    bool _isAlive;
    Paddle* _paddle;
    Ball* _ball;
    sf::Vector2f _direction;

    // Render
    sf::CircleShape _sprite;
    sf::Color _colour;
    sf::RenderWindow* _window;

};
