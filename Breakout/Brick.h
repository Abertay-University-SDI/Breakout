#pragma once
#include <SFML/Graphics.hpp>

class GameManager;  // forward declaration


class Brick {
public:
    Brick(float x, float y, float width, float height, sf::RenderWindow* window, float velocity, GameManager* gameManager, sf::Vector2f direction, sf::Color color);
    void render();
    void update(float dt);
    sf::FloatRect getBounds() const;

    sf::Vector2f getMiddle();

    float _bulletCooldown = 0.0f;

    bool _isDestroyed;

private:
    sf::RectangleShape _shape;
    sf::Vector2f _direction;
    sf::RenderWindow* _window;
    float _velocity;

    GameManager* _gameManager;  // Reference to the GameManager
};