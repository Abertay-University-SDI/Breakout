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
    void setFrenzyBall(float duration);
    void setPosition(float x, float y);
    void setDirection(const sf::Vector2f& direction);
    void normaliseDirection();
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const; 

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _isFrenzyBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager; 

    static constexpr float RADIUS = 10.0f;
    static constexpr float VELOCITY = 350.0f;  
};