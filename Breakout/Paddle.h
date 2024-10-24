#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window);
    ~Paddle();
    void handleInput(float dt);
    void moveLeft(float dt);
    void moveRight(float dt);
    void mousePositionInput(float dt);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _usingMouseInput;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
