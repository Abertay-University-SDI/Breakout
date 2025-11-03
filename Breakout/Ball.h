#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, sf::RenderTexture* renderTex, sf::RenderTexture* lightTex);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
    sf::Vector2f getPos();

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    sf::RenderTexture* _renderTex;
    sf::RenderTexture* _lightTex;
    sf::CircleShape _light;
    sf::Texture _lightSpriteTex;
    float _lightHitTime = 0.0f;
    float _lightFlickerTime = 0.0f;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager

    const float HIT_PULSE_TIME = 0.4f;
    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

