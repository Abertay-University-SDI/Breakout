#include "Camera.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Camera::Camera(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
    _view = _window->getView();
    _centre = sf::Vector2f(_view.getSize().x / 2, _view.getSize().y / 2);
    _view.setCenter(_centre);

    _shakeVal = 0;
    _offset = sf::Vector2f(0, 0);
}

Camera::~Camera()
{}

void Camera::update(float dt)
{
    if (_shakeVal <= 0)
    {
        _view.setCenter(_centre);
        _view.setRotation(0);
        _window->setView(_view);
        return; //stop update
    }

    //juice effects
    _offset.x = ((rand() % 100) - 50) * _shakeVal; //random num between -50 and 50
    _offset.y = ((rand() % 100) - 50) * _shakeVal;
    _offsetRot = ((rand() % 1) - 0.5) * _shakeVal; //random num between -0.5 and 0.5

    _view.setCenter(sf::Vector2f(_view.getCenter() + _offset));
    _view.setRotation(_view.getRotation() + _offsetRot);
    _window->setView(_view);

    //time += sf::seconds(dt);
    _shakeVal -= 0.07;
    std::cout << _shakeVal << std::endl;
}

void Camera::render()
{
    
}

void Camera::shake()
{
    _shakeVal += 1;
    //time = sf::seconds(0);
}

float Camera::getShakeVal()
{
    //std::cout << _shakeVal;
    return _shakeVal;
}