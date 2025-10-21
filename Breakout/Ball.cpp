#include "Ball.h"
#include "GameManager.h"

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFrenzyBall(false), _isFireBall(false), _isAlive(true), _direction({ 1,1 })
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(300, 300);
    //normalise the direction of the ball
    normaliseDirection(); 
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    //check for powerup, tick down or correct
    if (_timeWithPowerupEffect > 0.f)
    {
        _timeWithPowerupEffect -= dt;
    }
    else
    {
        if (_velocity != VELOCITY)
            _velocity = VELOCITY;  
        else
        {
            //disable fireball
            setFireBall(0);   
            //disable frenzyball
            setFrenzyBall(0);    
            //return ball back to normal colour.
            _sprite.setFillColor(sf::Color::Cyan);  
        }
    }

    // Fireball effect
    if (_isFireBall)
    {
        // Flickering effect
        int flicker = rand() % 50 + 205; // Random value between 205 and 255
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
    }

    // Frenzyball effect
    if (_isFrenzyBall)
    {
        //make the ball red
        _sprite.setFillColor(sf::Color::Red);
    }

    // Update position
    _sprite.move(_direction * _velocity * dt);

    //check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    //bouncing on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
        normaliseDirection();
        //shake when it hits the wall
        _gameManager->triggerShake(0.1f, 2.0f);
        //play the wall hit sound
        _gameManager->playWallHitSound(); 
    }

    //bouncing on roof
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
        normaliseDirection();
        //shake when it hits the roof
        _gameManager->triggerShake(0.1f, 2.0f);
        //play the wall hit sound
        _gameManager->playWallHitSound();
    }

    //losing a life bounce
    if (position.y > windowDimensions.y)
    {
        _gameManager->loseLife();
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        //bounce vertically
        _direction.y *= -1; 
        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;
        //normalise after paddle hit
        normaliseDirection(); 
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
        //shake when it hits the paddle
        _gameManager->triggerShake(0.1f, 4.0f); 
        //play the paddle hit sound
        _gameManager->playPaddleHitSound(); 
    }

    //collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall || _isFrenzyBall) return; //no collisions when in fireBall or frenzyBall mode
    if (collisionResponse == 1)
    {
        //bounce horizontally
        _direction.x *= -1;
        //normalise after hit
        normaliseDirection();
        //shake on brick hit
        _gameManager->triggerShake(0.1f, 4.0f); 
        //play the brick hit sound
        _gameManager->playBrickHitSound(); 
    }
    else if (collisionResponse == 2)
    {
        //bounce vertically
        _direction.y *= -1; 
        //normalise after hit
        normaliseDirection();
        //shake on brick hit
        _gameManager->triggerShake(0.1f, 4.0f);
        //play the brick hit sound
        _gameManager->playBrickHitSound();
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

void Ball::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}

void Ball::setDirection(const sf::Vector2f& direction)
{
    _direction = direction;
    normaliseDirection();
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

void Ball::setFrenzyBall(float duration)
{
    if (duration)
    {
        _isFrenzyBall = true;
        _timeWithPowerupEffect = duration;
        return;
    }
    _isFrenzyBall = false;
    _timeWithPowerupEffect = 0.f;
}

void Ball::normaliseDirection()
{
    float norm = std::sqrt(_direction.x * _direction.x + _direction.y * _direction.y);
    if (norm > 0.f)
    {
        _direction /= norm;
    }
    else
    {
        _direction = sf::Vector2f(0.f, 1.f); 
    }
}

sf::Vector2f Ball::getPosition() const
{
    return _sprite.getPosition();
}

sf::FloatRect Ball::getBounds() const
{
    return _sprite.getGlobalBounds();
}