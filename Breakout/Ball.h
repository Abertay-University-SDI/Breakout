#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Ball {
public:
    Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager,sf::Color colour);
    ~Ball();
    void update(float dt);
    void render();
    void setVelocity(float coeff, float duration);
    void setFireBall(float duration);
	void setPrimary(bool isPrimary) { this->isPrimary = isPrimary; }
	void setColour(sf::Color color) { _sprite.setFillColor(color); }
	void reset(); 
private:
    sf::CircleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    sf::Color _color;
    float _velocity;
    bool _isAlive;
    bool _isFireBall;
    bool isPrimary = false;
    float _timeWithPowerupEffect;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float RADIUS = 10.0f;      
    static constexpr float VELOCITY = 350.0f;   // for reference.
};

