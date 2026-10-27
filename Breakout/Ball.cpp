#include "Ball.h"
#include "Raymarch.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1}),
    _baseVelocity(VELOCITY), _isLaunched(false)
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(ballColour);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    // waiting to be served: ride on top of the paddle
    if (!_isLaunched)
    {
        sf::FloatRect paddle = _gameManager->getPaddle()->getBounds();
        _sprite.setPosition(paddle.left + paddle.width / 2 - RADIUS, paddle.top - 2 * RADIUS);
        return;
    }

    // check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != _baseVelocity)
            _velocity = _baseVelocity;   // reset speed.
        else
        {
            setFireBall(0);    // disable fireball
            _sprite.setFillColor(ballColour);  // back to normal colour.
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
        reset();
        _gameManager->loseLife();
        return;
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);

        // splash where the ball met the paddle
        _gameManager->getParticles()->splash(
            { _sprite.getPosition().x + RADIUS, _gameManager->getPaddle()->getBounds().top }, _sprite.getFillColor(), 8);
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
    Raymarch::add(_sprite);
}

void Ball::setVelocity(float coeff, float duration)
{
    _velocity = coeff * _baseVelocity;
    _timeWithPowerupEffect = duration;
}

void Ball::setSpeedScale(float scale)
{
    _baseVelocity = scale * VELOCITY;
}

void Ball::reset()
{
    _isLaunched = false;
    setFireBall(0);
    _velocity = _baseVelocity;
    _sprite.setFillColor(ballColour);
}

void Ball::launch()
{
    _isLaunched = true;
    _direction = { (rand() % 2) ? 0.5f : -0.5f, -1.f };   // up, slightly to one side
}

bool Ball::isLaunched() const
{
    return _isLaunched;
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
