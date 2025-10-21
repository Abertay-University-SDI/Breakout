#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
   
    // Spawn new ball at random side of map.
    float x = (rand() % 2 == 0) ? 0.f : _window->getSize().x - (2 * RADIUS);
    _sprite.setPosition(x, 300);
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

    // Ball trail.
    sf::Color trailColour;
    trailColour.r = static_cast<sf::Uint8>(_sprite.getFillColor().r * 0.8f);
    trailColour.g = static_cast<sf::Uint8>(_sprite.getFillColor().g * 0.8f);
    trailColour.b = static_cast<sf::Uint8>(_sprite.getFillColor().b * 0.8f);

    TrailDot dot;
    dot.shape = sf::CircleShape(RADIUS);
    dot.shape.setPosition(_sprite.getPosition());
    dot.shape.setFillColor(trailColour);
    dot.lifetime = 0.5f; // seconds
    _trail.push_back(dot);

    // Trail fade.
    for (auto it = _trail.begin(); it != _trail.end(); )
    {
        it->lifetime -= dt;
        if (it->lifetime <= 0.f)
        {
            it = _trail.erase(it);
        }
        else
        {
            sf::Color color = it->shape.getFillColor();
            color.a = static_cast<sf::Uint8>(255 * (it->lifetime / 1.0f)); // fade based on lifetime
            it->shape.setFillColor(color);
            ++it;
        }
    }

    // check bounds and bounce
    sf::Vector2f position = _sprite.getPosition();
    sf::Vector2u windowDimensions = _window->getSize();

    // bounce on walls
    if ((position.x >= windowDimensions.x - 2 * RADIUS && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
    {
        _direction.x *= -1;
        _gameManager->getAudioManager()->playSound("wall_hit");
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;
        _gameManager->getAudioManager()->playSound("wall_hit");
    }

    // lose life bounce
    if (position.y > windowDimensions.y)
    {
        float x = (rand() % 2 == 0) ? 0.f : _window->getSize().x - (2 * RADIUS);
        _sprite.setPosition(x, 300);
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

        // Play sound when ball hits paddle.
        _gameManager->getAudioManager()->playSound("paddle_hit");
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
    for (const auto& dot : _trail)
    {
        _window->draw(dot.shape);
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
