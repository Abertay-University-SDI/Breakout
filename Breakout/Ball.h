#pragma once
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"


class GameManager;  // forward declaration
class ExplodeParticle;
class Particle;


class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

    void triggerParticles();

    sf::Vector2f getPosition(bool centre = false);

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager

    sf::SoundBuffer bounceBuffer;
    sf::Sound bounceSound;

    sf::SoundBuffer collectBuffer;
    sf::Sound collectSound;

    int successiveCollects{ 0 };

    std::vector<std::unique_ptr<Particle>> particles;


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

