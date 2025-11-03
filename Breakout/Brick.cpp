#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, Ball* ball, sf::RenderTexture* renderTex, sf::RenderTexture* lightTex, sf::Texture* lightSpriteTex)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
    _shape.setOutlineColor(sf::Color(120, 0, 0, 255));
    _shape.setOutlineThickness(2);

    _ball = ball;
    _eye = new Eye(8, renderTex, ball);
    int maxX = 25;
    int offsetX = std::rand() % (maxX * 2 + 1);
    offsetX -= maxX;

    int maxY = 5;
    int offsetY = std::rand() % (maxY * 2 + 1);
    offsetY -= maxY;
    _eye->setPos(sf::Vector2f(x - 8 + width * 0.5f + offsetX, y + 8 + offsetY));
    _lightTex = lightTex;
    _light.setTexture(lightSpriteTex);
    _light.setFillColor(sf::Color(255, 100, 100, 40 * 0.5f));
    _lightFlickerTimer += std::rand() % (20);
}

void Brick::render(sf::RenderWindow& window, sf::RenderTexture* renderTex)
{
    if (!_isDestroyed) {
        //window.draw(_shape);
        renderTex->draw(_shape);
        _eye->render();
        _lightTex->draw(_light);
    }
}

void Brick::update(float dt)
{
    _lightFlickerTimer += dt * 2;
    float rad = 7;
    float currRad = rad * (10 - sin(_lightFlickerTimer) * 4);
    _light.setRadius(currRad);
    _light.setPosition(_shape.getPosition() + sf::Vector2f(_shape.getGlobalBounds().width * 0.5f, 0) - sf::Vector2f(currRad - rad, currRad - rad));
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}
