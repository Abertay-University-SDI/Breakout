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
    void mouseMove(float xPos);
    void update(float dt);
    void reset();
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);
    void setVelocity(float vel, float duration);

    bool getMouseControl()
    {
        return _mouseControl;
    }

    void setMouseControl(bool mc)
    {
        _mouseControl = mc;
    }

    void setBeastMode(bool b)
    {
        beastMode = b;
        setWidth(1.0f, 0.0f);
    }

private:


    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    bool _mouseControl;
    bool beastMode;
    float _velocity;
    float _timeInPowerup = 0.0f;

};
