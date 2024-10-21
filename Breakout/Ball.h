#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, Paddle* paddle);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setStickyBall(float duration);
    bool getIsStickyBall();
    int getCollisionResponce();
    void setIsStuck(bool stuck);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    Paddle* _paddle;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isStickyBall;
    float _timeWithPowerupEffect;
    int collisionResponse;
    bool _isStuck = false;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

