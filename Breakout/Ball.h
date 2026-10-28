#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, float x_pos, float y_pos);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setMultiBall(float duration);
    void setDirection(sf::Vector2f direction);
    void setMultiVelocity(float multiVelocity);
    void setMultiPosition(sf::Vector2f multiPosition);
    void setMultiColour();
    sf::Vector2f getBallPosition();

private:
    
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isMultiBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager


         
    static constexpr float VELOCITY = 350.0f;   // for reference.

protected:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    static constexpr float RADIUS = 10.0f;
};

