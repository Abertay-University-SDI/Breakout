#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

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
    float m_time;
    bool m_isAlive;
    Paddle* m_paddle;
    Ball* m_ball;
    sf::Vector2f m_direction;

    // Render
    sf::CircleShape m_sprite;
    sf::Color m_colour;
    sf::RenderWindow* m_window;

};
