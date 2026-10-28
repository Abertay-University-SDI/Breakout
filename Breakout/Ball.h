#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <deque>
#include <cstdint>

class GameManager;  // forward declaration

struct Trail
{
    sf::Vector2f pos;
    float age;
    sf::Color col;
};


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

    sf::SoundBuffer patBuff;
    sf::Sound patS;
    int patC = 0;
    void playPat();

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

