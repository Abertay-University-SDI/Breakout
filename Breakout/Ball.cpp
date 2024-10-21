#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    _paddleSoundBuffer.loadFromFile("audio/paddleSound.wav");  //load sound into buffer
    _paddleSound.setBuffer(_paddleSoundBuffer);   //set paddleSound variable correctly

    _blockSoundBuffer.loadFromFile("audio/blockSound.wav");  //load sound into buffer
    _blockSound.setBuffer(_blockSoundBuffer);   //set paddleSound variable correctly
}

Ball::~Ball()
{
}

void Ball::update(float dt)
{
    if (_timeInNewSize > 0)
    {
        _timeInNewSize -= dt;
    }
    else
    {
        _sprite.setRadius(RADIUS); // Reset to default width after duration
    }

    _previousPositions.push_back(_sprite.getPosition());    //adds the current position to the vector

    //if the number of points in the trail has gone above the maximum then remove the oldest point in the trail
    if (_previousPositions.size() > _numberOfTrails)
    {
        _previousPositions.erase(_previousPositions.begin());
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

        _paddleSound.play();    //play audio
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall)
    {
        _blockSound.play();
        return; // no collisisons when in fireBall mode.
    }
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
        _blockSound.play();
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
        _blockSound.play();
    }
}

void Ball::render()
{
    for (int i = 0; i < _previousPositions.size(); i++) //run through every position in the vector
    {
        //create a circle and set it to a semi-transparent green colour
        _trailSprite.setRadius(RADIUS); 
        _trailSprite.setFillColor(sf::Color(0.f, 255.f, 0.f, 2.f));

        //set the position to the current position in the vector
        _trailSprite.setPosition(_previousPositions[i]);

        _window->draw(_trailSprite);//draw the sprite
    }

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

void Ball::setRadius(float rad, float duration)
{
    float newRadius = rad * RADIUS;
    _sprite.setRadius(newRadius);
    _timeInNewSize = duration;
}