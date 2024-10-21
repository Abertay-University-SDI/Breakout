#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    void setRadius(float rad, float duration);
    sf::Sound _paddleSound;     //audio for ball hitting paddle
    sf::Sound _blockSound;     //audio for ball hitting blocks

private:
    sf::CircleShape _sprite;
    sf::CircleShape _trailSprite;   //sprite to be drawn in the trail
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    sf::SoundBuffer _paddleSoundBuffer;   //buffer for loading paddle sound
    sf::SoundBuffer _blockSoundBuffer;   //buffer for loading block sound
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;
    std::vector<sf::Vector2f> _previousPositions;   //a vector to store where the ball has come from to create a trail
    int _numberOfTrails = 200;   //how long the trail should be/how many previous points it should display
    float _timeInNewSize = 0;
        
    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

