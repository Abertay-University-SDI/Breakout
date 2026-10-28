#include "PowerupBase.h"
#include <cmath>
#include <iostream>
#include "ExtraLife.h"
#include "GameManager.h" // avoid cicular dependencies

ExtraLife::ExtraLife(sf::RenderWindow* window, Paddle* paddle, Ball* ball, sf::Vector2f spawnX, GameManager* gamemanager)
{
    _window = window;
    _paddle = paddle;
    _sprite.setRadius(EXTRA_LIFE_RADIUS);
    _isAlive = true;
    _ball = ball;
    _gameManager = gamemanager;

    // Initial position and direction with some variability
    sf::Vector2f initialSpawn = spawnX;
    _sprite.setPosition(initialSpawn);
    _direction = { 0.0f, EXTRA_LIFE_SPEED };
}

void ExtraLife::update(float dt)
{
    _time += dt; // Increment time

    // Smooth side-to-side movement using a sine wave
    float sineWave = std::sin(_time * 2.0f); // Adjust the frequency as needed
    _direction.x = sineWave * AMPLITUDE_OF_FALL; // Adjust the amplitude as needed

    // Move the extra life
    _sprite.move(_direction.x * dt, _direction.y * dt);

    //// Smooth color changes
    //for (int i = 0; i < _colours.size(); ++i)
    //{
    //    _colours[i] += 50 * dt; // Increment smoothly over time
    //    if (_colours[i] > 255) _colours[i] -= 255; // Wrap around to stay within valid range
    //}
    //_sprite.setFillColor(sf::Color(static_cast<sf::Uint8>(_colours[0]), static_cast<sf::Uint8>(_colours[1]), static_cast<sf::Uint8>(_colours[2]), 255));

    // Collide with floor (i.e., was missed)
    if (_sprite.getPosition().y + EXTRA_LIFE_RADIUS * 2 >= _window->getSize().y)
    {
        _isAlive = false;
    }
}
void ExtraLife::render()
{
    _window->draw(_sprite);
}

bool ExtraLife::checkCollisionWithPaddle()
{
    if (_sprite.getGlobalBounds().intersects(_paddle->getBounds()))
    {
        //if collided with paddle
        _isAlive = false;
       // _gameManager->addLife(); 
        return true;
    }
    return false;
}

void ExtraLife::setAlive(bool alive)
{
    _isAlive = alive;
}
bool ExtraLife::isAlive()
{
    return _isAlive;
}
