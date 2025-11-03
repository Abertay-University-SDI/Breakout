#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

#include "Eye.h"

class Brick {
public:
    Brick(float x, float y, float width, float height, Ball* ball, sf::RenderTexture* renderTex, sf::RenderTexture* lightTex, sf::Texture* lightSpriteTex);
    void render(sf::RenderWindow& window, sf::RenderTexture* renderTex);
    void update(float dt);
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    Ball* _ball;
    Eye* _eye;
    sf::RenderTexture* _lightTex;
    sf::CircleShape _light;
    float _lightFlickerTimer = 0;
};