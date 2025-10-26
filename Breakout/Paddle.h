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
    void setFreeMove();
    void freeMove(float dt);
    void update(float dt);
    void render();
    float getPaddleWidth();
    float getPaddleHeight();
    sf::Vector2f getPaddlePos();
    bool getFreeMove();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

    bool _isFreeMove;

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _powerUpTimer;
    float _timeInNewSize = 0.0f;
};
