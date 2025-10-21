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
    sf::CircleShape m_sprite;
    sf::Vector2f m_direction;
    sf::RenderWindow* m_window;
    float m_velocity;
    bool m_isAlive;
    bool m_isFireBall;
    float m_timeWithPowerupEffect;

    GameManager* m_gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

