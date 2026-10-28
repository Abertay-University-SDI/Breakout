#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball() = default;
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, sf::Color _colour);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);


    auto getPosition() -> sf::Vector2f;
    auto setPosition(sf::Vector2f position) -> void;
    auto setDirection(sf::Vector2f direction) -> void;
    auto getDirection() -> sf::Vector2f;


    auto setColour(sf::Color& colour) -> void;
    auto getColour() -> sf::Color&;
    auto setIsMainBall(bool _maiBall) -> void;

    auto setAlive(bool alive) -> void;
    auto getAlive() -> bool;
    auto setAllowSplit(bool split, float duration) -> void;
    auto GetID() -> int;

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    sf::Color colour;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool _split;
    bool isMainBall;

    float _timeWithPowerupEffect;

    int id;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 400.0f;   // for reference.
};

