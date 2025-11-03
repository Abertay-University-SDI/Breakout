#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void speedBooster(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);
    sf::RectangleShape _sprite;

private:

    float speed = PADDLE_SPEED;
    sf::RenderWindow* _window;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
