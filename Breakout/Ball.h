#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenShakeManager.h"


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, ScreenShakeManager* screenShakeManager, sf::Texture* tex, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);

private:
    sf::Sprite _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    ScreenShakeManager* _screenShakeManager;

    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    float _timeWithPowerupEffect;
    int _radius;

    GameManager* _gameManager;  // Reference to the GameManager

    static constexpr int SCALE = 2.0f;
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

