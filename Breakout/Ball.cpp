#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>
#include <math.h>

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    _window = window;
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);

        if (_isNewBall == true)
        {
            _ballOnPaddle = true;
            _direction = sf::Vector2f(0, 0);
        }
    }

    if (_ballOnPaddle == true)
    {
        _sprite.setPosition(_gameManager->getPaddle()->getPaddlePos().x + _gameManager->getPaddle()->getPaddleWidth() / 2, _gameManager->getPaddle()->getPaddlePos().y - _gameManager->getPaddle()->getPaddleHeight());

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (_direction == sf::Vector2f(0, 0) && _gameManager->getPaddle()->getFreeMove() == false)
            {

                //if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                //{
                mousePos = sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);
                std::cout << mousePos.x * 0.001f << " " << mousePos.y * 0.001f;
                _direction.x = atan(mousePos.x - _sprite.getPosition().x);
                _direction.y = atan(mousePos.y - _sprite.getPosition().y);
                _velocity = 7;
                isColliding = false;
                _ballOnPaddle = false;
                _isNewBall = false;
                //}
            }
            else if (_direction == sf::Vector2f(0, 0) && _gameManager->getPaddle()->getFreeMove() == true)
            {
                _velocity = 3;
                _direction.y = 1;
                isColliding = false;
                _ballOnPaddle = false;
                _isNewBall = false;
            }
        }
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
    }
}

void Ball::render()
{
    _window->draw(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * VELOCITY;
    _timeWithPowerupEffect = duration;
}

void Ball::setFireBall(float duration)
{
    if (duration) 
    {
        _isFireBall = true;
        _timeWithPowerupEffect = duration;        
        return;
    }
    _isFireBall = false;
    _timeWithPowerupEffect = 0.f;    
}

void Ball::setNewBall()
{

    _isNewBall = true;

    if (_isNewBall == true && isColliding == true) 
    {
        _isNewBall = false;
        isColliding = false;
    }

}
