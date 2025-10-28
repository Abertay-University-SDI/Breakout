#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration
class LivesCounter;


class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, LivesCounter* livesCounter);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff);
    void addFireBall() { _fireBallCount++; }
    void addSticky() { _StickyBallCount++; }
    void addGodmode() { _GodmodeCount++; }
    void subFireBall() { _fireBallCount--; }
    void subSticky() { _StickyBallCount--; }
    void subGodmode() { _GodmodeCount--; }
    void setSize(float coeff);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;

    int _fireBallCount{ 0 };
    int _StickyBallCount{ 0 };
    int _GodmodeCount{ 0 };

    bool _isStuck;
    sf::Vector2f _stuckDirection;

    GameManager* _gameManager;  // Reference to the GameManager
    LivesCounter* _livesCounter;

    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

