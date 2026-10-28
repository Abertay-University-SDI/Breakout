#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include <vector>

class GameManager;  // forward declaration

class ExtraLife
{
public:
    ExtraLife(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Vector2f spawnX, GameManager* gamemanager);

    void update(float dt);
    void render();

    bool checkCollisionWithPaddle();

    void setAlive(bool alive);
    bool isAlive();

protected: // Protected so derived classes can access these members
    // Constants
    static constexpr float AMPLITUDE_OF_FALL = 80.0f;   // waviness of fall

    // Game logic
    float _time;
    bool _isAlive;
    Paddle* _paddle;
    Ball* _ball;
    sf::Vector2f _direction;

    GameManager* _gameManager; 

    // Render
    sf::CircleShape _sprite;
    sf::Color _colour;
    sf::RenderWindow* _window;
};

