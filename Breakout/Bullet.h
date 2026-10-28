#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Bullet {
public:
    Bullet(sf::RenderWindow* window, float velocity, GameManager* gameManager);
    ~Bullet();
    void update(float dt);
    void render();

    void setPosition(sf::Vector2f position);

    bool _isDestroyed;

private:
    sf::RectangleShape _sprite;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;

    GameManager* _gameManager;  // Reference to the GameManager


    static constexpr float VELOCITY = 350.0f;   // for reference.
};

