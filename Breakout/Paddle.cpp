#include "Paddle.h"
#include <iostream>

Paddle::Paddle(sf::RenderWindow* window, sf::RenderTexture* renderTex, Ball* ball, sf::RenderTexture* lightTex)
    : _window(window), _width(PADDLE_WIDTH), _timeInNewSize(0.0f), _isAlive(true), _lightTex(lightTex)
{

    _light.setFillColor(sf::Color(155, 77, 158, 150 * 0.5f));
    _sprite.setOutlineColor(sf::Color(155, 77, 158, 255));
    _sprite.setOutlineThickness(3);
    _sprite.setFillColor(sf::Color(224, 123, 219, 255));
    _sprite.setPosition((window->getSize().x - _width) / 2.0f, window->getSize().y - 50.0f);
    _sprite.setSize(sf::Vector2f(_width, PADDLE_HEIGHT));
    leftEye = new Eye(15, renderTex, ball, sf::Color(224, 123, 219, 255));
    rightEye = new Eye(15, renderTex, ball, sf::Color(224, 123, 219, 255));
    _renderTex = renderTex;

    _lightSpriteTex.loadFromFile("pointLight.png");
    _light.setTexture(&_lightSpriteTex);
}

Paddle::~Paddle()
{
}

void Paddle::moveLeft(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && position > 0)
    {
        _sprite.move(sf::Vector2f(-dt * PADDLE_SPEED, 0));
    }
}

void Paddle::moveRight(float dt)
{
    float position = _sprite.getPosition().x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && position < _window->getSize().x - _width)
    {
        _sprite.move(sf::Vector2f(dt * PADDLE_SPEED, 0));
    }
}

void Paddle::setPos(float x)
{
    _sprite.setPosition(sf::Vector2(x, _sprite.getPosition().y));
    sf::Vector2f currPos = _sprite.getPosition();
    leftEye->setPos(currPos + sf::Vector2f(10, 5));
    rightEye->setPos(currPos + sf::Vector2f(getBounds().width - 10 - 30,  5));
}

void Paddle::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        setWidth(1.0f, 0.0f); // Reset to default width after duration
    }

    _lightFlickerTime += dt * 7;
    float rad = 12;
    float currRad = rad * (10 - sin(_lightFlickerTime));
    _light.setRadius(currRad);
    _light.setPosition(_sprite.getPosition() + (sf::Vector2f(getBounds().width * 0.5f, 0)) - sf::Vector2f(currRad, currRad));
}

void Paddle::render()
{
   // _window->draw(_sprite);
    _renderTex->draw(_sprite);
    rightEye->render();
    leftEye->render();
    _lightTex->draw(_light);
}

sf::FloatRect Paddle::getBounds() const
{
    return _sprite.getGlobalBounds();
}

// update width by SF of coeff. 
// ensure centre remains consistent.
void Paddle::setWidth(float coeff, float duration)
{
    _width = coeff * PADDLE_WIDTH;
    _sprite.setSize(sf::Vector2f(_width, _sprite.getSize().y));
    _timeInNewSize = duration;
    float newX = _sprite.getPosition().x + (_width - PADDLE_WIDTH) / 2;
    _sprite.setPosition(newX, _sprite.getPosition().y);
}
