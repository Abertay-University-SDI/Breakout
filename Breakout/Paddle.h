#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class GameManager;

class Paddle
{
public:
    Paddle(sf::RenderWindow* window, GameManager* gameManager);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    sf::FloatRect getBounds1() const;
    void setWidth(float coeff, float duration);

private:

    GameManager* _gameManager;
    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    sf::RectangleShape _sprite1;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
