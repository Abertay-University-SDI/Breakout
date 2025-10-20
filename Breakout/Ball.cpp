#include "Ball.h"
#include "Paddle.h"
#include "BrickManager.h"
#include "GameManager.h" 

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _brickHitPitch = 0.2;
    _brickHitVolume = 60;

    _hitSoundBuffer.loadFromFile("Audio/Ding.wav");
    _audioSource.setBuffer(_hitSoundBuffer);   /// Load Audio File and insert into the audio Source
    _audioSource.setVolume(_brickHitVolume);

    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    _screenShakeOnCollideBrickLength = 0.2;
    _screenShakeOnFireBallLength = 2;
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

        _brickHitPitch = 0; // Rest Pitch Sound when the ball hits the paddle
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);

    if (_isFireBall)
    {
        _gameManager->startScreenShake(_screenShakeOnFireBallLength);

    }
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
        playDing();
        _gameManager->startScreenShake(_screenShakeOnCollideBrickLength);
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
      
        playDing();
        _gameManager->startScreenShake(_screenShakeOnCollideBrickLength);

    }

}

void Ball::playDing() // with every hit increase pitch 
{
    float increaseAmount = 0.2f;


    if (_brickHitPitch > 0.9)
    {
        increaseAmount = 0.1;
    }
    else {
        _brickHitPitch += increaseAmount;

    }
    
    _audioSource.setPitch(_brickHitPitch);
    _audioSource.play();
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
