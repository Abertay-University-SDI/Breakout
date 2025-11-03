#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager, sf::RenderTexture* renderTex, sf::RenderTexture* lightTex)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1}), _lightTex(lightTex)
{
    _lightSpriteTex.loadFromFile("pointLight.png");
    _light.setTexture(&_lightSpriteTex);
    _light.setRadius(RADIUS * 10);
    _sprite.setRadius(RADIUS);
    //_sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);
    _renderTex = renderTex;
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
            _sprite.setFillColor(sf::Color::White);  // back to normal colour.
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
        _lightHitTime = HIT_PULSE_TIME;
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
        _lightHitTime = HIT_PULSE_TIME;
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

        _lightHitTime = HIT_PULSE_TIME;
    }

    _lightFlickerTime += dt * 20;
    if (_lightHitTime > 0)
    {
        _lightHitTime -= dt;
        _lightHitTime = std::clamp(_lightHitTime, 0.0f, 9999.0f);
    }
    float currRad = RADIUS * (10 - sin(_lightFlickerTime));//+ (_lightHitTime / HIT_PULSE_TIME) * 50;
    _light.setFillColor(sf::Color(255, 255, 255, (255 * 0.5f) + (_lightHitTime / HIT_PULSE_TIME) * 255 * 0.5f));
    _light.setRadius(currRad);
    _light.setPosition(_sprite.getPosition() - sf::Vector2f(currRad - RADIUS, currRad - RADIUS));

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
        _lightHitTime = HIT_PULSE_TIME;
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
        _lightHitTime = HIT_PULSE_TIME;
    }
}

void Ball::render()
{
    //_window->draw(_sprite);
    _renderTex->draw(_sprite);
    _lightTex->draw(_light);
}

sf::Vector2f Ball::getPos()
{
    return _sprite.getPosition();
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
