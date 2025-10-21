#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle();
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

private:

    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
