#pragma once

#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Eye.h"

class Paddle
{
public:
    Paddle(sf::RenderWindow* window, sf::RenderTexture* renderTex, Ball* ball, sf::RenderTexture* lightTex);
    ~Paddle();

    void moveLeft(float dt);
    void moveRight(float dt);
    void setPos(float x);
    void update(float dt);
    void render();
    sf::FloatRect getBounds() const;
    void setWidth(float coeff, float duration);

private:

    Eye* leftEye;
    Eye* rightEye;
    sf::CircleShape _light;
    sf::Texture _lightSpriteTex;
    sf::RenderTexture* _renderTex;
    sf::RenderTexture* _lightTex;
    sf::RenderWindow* _window;
    sf::RectangleShape _sprite;
    float _lightFlickerTime;
    float _width = PADDLE_WIDTH;
    bool _isAlive;
    float _timeInNewSize = 0.0f;
};
