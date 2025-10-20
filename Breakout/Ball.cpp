#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({ 1,1 }), _isBallRespawning(true), _respawnHold(RESPAWN_TIME_DELAY), _respawnBlinkTimer(RESPAWN_BLINK_ON_DURATION), _currentPowerup(POWERUPS::none)
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    //wait to respawn the ball, blink the ball while it is waiting
    if (_isBallRespawning) {
        if (_respawnHold > 0.f) _respawnHold -= dt;
        if (_respawnBlinkTimer > 0.f) _respawnBlinkTimer -= dt;

        if (_respawnBlinkTimer <= 0.f) {
            if (_sprite.getFillColor() == sf::Color::Cyan) {
                _sprite.setFillColor(sf::Color::Transparent);
                _respawnBlinkTimer = RESPAWN_BLINK_OFF_DURATION;
            }
            else if (_sprite.getFillColor() == sf::Color::Transparent) {
                _sprite.setFillColor(sf::Color::Cyan);
                _respawnBlinkTimer = RESPAWN_BLINK_ON_DURATION;
            }
            
        }
        if (_respawnHold <= 0.f) {
            _respawnHold = RESPAWN_TIME_DELAY;
            _respawnBlinkTimer = RESPAWN_BLINK_ON_DURATION;
            _isBallRespawning = false;
            _sprite.setFillColor(sf::Color::Cyan);
        }
        return;
    }

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
            setPowerup(0, POWERUPS::none);    // disable powerup
            _sprite.setFillColor(sf::Color::Cyan);  // back to normal colour.
        }        
    }

    int flicker = rand() % 50 + 205; // Random value between 205 and 255
    switch (_currentPowerup)
    {
    case fireBall:

        // Flickering effect
        
        _sprite.setFillColor(sf::Color(flicker, flicker / 2, 0)); // Orange flickering color
        break;

    case bombBall:

        // Flickering effect
        _sprite.setFillColor(sf::Color(255, 255, 0)); // Orange flickering color
        break;
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
        resetBall();
        _gameManager->loseLife();
        _isBallRespawning = true;
    }

    // collision with paddle
    if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
    {
        _direction.y *= -1; // Bounce vertically

        float paddlePositionProportion = (_sprite.getPosition().x - _gameManager->getPaddle()->getBounds().left) / _gameManager->getPaddle()->getBounds().width;
        _direction.x = paddlePositionProportion * 2.0f - 1.0f;

        // Adjust position to avoid getting stuck inside the paddle
        _sprite.setPosition(_sprite.getPosition().x, _gameManager->getPaddle()->getBounds().top - 2 * RADIUS);
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction, _currentPowerup);
    if (_currentPowerup == POWERUPS::fireBall) return; // no collisisons when in fireBall mode.
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

void Ball::resetBall()
{
    _sprite.setPosition(0, 300);
    _direction = { 1, 1 };
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

void Ball::setPowerup(float duration, POWERUPS newpowerup)
{
    if (duration)
    {
        _currentPowerup = newpowerup;
        _timeWithPowerupEffect = duration;
        return;
    }
    _currentPowerup = none;
    _timeWithPowerupEffect = 0.f;
}

POWERUPS Ball::getPowerup()
{
    return _currentPowerup;
}
