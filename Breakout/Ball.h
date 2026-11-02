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

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager

    std::vector<sf::CircleShape> _spriteTrail;
    static constexpr int NUM_TRAIL_ELEMENTS = 100;
    static constexpr float TRAIL_END_SCALE = 0.1f;
    static constexpr float TRAIL_SPACING = 2.0f;
    inline static const sf::Color TRAIL_END_COLOUR = sf::Color::Red;

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

