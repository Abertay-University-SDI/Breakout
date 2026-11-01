#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff);
	void setPower(float value);

	int getBounces() const { return _bounces; }  // Getter for the number of bounces

private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;
    bool _isAlive;
    float _power = BALL_DEFAULT_DAMAGE;
    float _timeWithPowerupEffect;
	int _bounces = 0;  // Number of bounces since the last power-up effect

    GameManager* _gameManager;  // Reference to the GameManager
};

