#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setSpeedScale(float scale);    // per-level speed, applied on top of VELOCITY
    void reset();                       // back on the paddle, waiting to be launched
    void launch();
    bool isLaunched() const;

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    float _baseVelocity;
    bool _isLaunched;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 15.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

