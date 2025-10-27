#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies
#include <iostream>

Ball::Ball(sf::RenderWindow* window, ScreenShakeManager* screenShakeManager, sf::Texture* tex, float velocity, GameManager* gameManager)
    : _window(window), _screenShakeManager(screenShakeManager), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setTexture(*tex);
    _sprite.setPosition(0, 300);
    _sprite.setScale(SCALE, SCALE);
    _radius = SCALE * _sprite.getTextureRect().getSize().y / 2;
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
            _sprite.setColor(sf::Color::White);  // back to normal colour.
        }        
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Update position with a subtle floating-point error
    _sprite.move(_direction * _velocity * dt);

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2f windowDimensions = _window->getView().getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * _radius && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
        _screenShakeManager->shake(5, 0.1f);
    }
    
    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
        _screenShakeManager->shake(5, 0.1f);
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        _sprite.setPosition(0, 300);
        _direction = { 1, 1 };
        _gameManager->loseLife();

        _screenShakeManager->shake(40, 0.5f);
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically
        _screenShakeManager->shake(5, 0.1f);

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * _radius);
    }

    // collision with bricks
    int brickCollisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction, _isFireBall);
    if (_isFireBall)
    {
        if (brickCollisionResponse != 0)
            _screenShakeManager->shake(10, 0.125f);
            
        return; // no collisisons when in fireBall mode.
    }
    if (brickCollisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
        _screenShakeManager->shake(10, 0.125f);
    }
    else if (brickCollisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
        _screenShakeManager->shake(10, 0.125f);
    }

    // move position forward a bit after brick hit to avoid double hits
    if (brickCollisionResponse != 0)
    {
        _sprite.move(_direction * 5.0f);
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
