#include "Ball.h"
#include "GameManager.h" // avoid cicular dependencies

#include "explodeParticle.h"
#include "Particle.h"

Ball::Ball(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager),
    _timeWithPowerupEffect(0.f), _isFireBall(false), _isAlive(true), _direction({1,1})
{
    _sprite.setRadius(RADIUS);
    _sprite.setFillColor(sf::Color::Cyan);
    _sprite.setPosition(0, 300);

    bounceBuffer.loadFromFile("sfx/bounce.wav");
    bounceSound.setBuffer(bounceBuffer);
    bounceSound.setVolume(25.0f);

    collectBuffer.loadFromFile("sfx/collect.wav");
    collectSound.setBuffer(collectBuffer);
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

        bounceSound.play();
    }

    // bounce on ceiling
    if (position.y <= 0 && _direction.y < 0)
    {
        _direction.y *= -1;

        bounceSound.play();
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

        bounceSound.play();
        successiveCollects = 0;
    }

    // collision with bricks
    int collisionResponse = _gameManager->getBrickManager()->checkCollision(_sprite, _direction);
    if (_isFireBall) return; // no collisisons when in fireBall mode.
    if (collisionResponse == 1)
    {
        _direction.x *= -1; // Bounce horizontally
        collectSound.setPitch(1.0f + successiveCollects * 0.1);
        collectSound.play();
        ++successiveCollects;

        triggerParticles();
    }
    else if (collisionResponse == 2)
    {
        _direction.y *= -1; // Bounce vertically
        collectSound.setPitch(1.0f + successiveCollects * 0.1);
        collectSound.play();
        ++successiveCollects;

        triggerParticles();
    }
    
    for (int i = particles.size() - 1; i >= 0; --i)
    {
        if (particles.at(i)->getActive())
        {
            particles.at(i)->update(dt);
        }
        else
        {
            particles.erase(particles.begin() + i);
        }

    }


}

void Ball::render()
{
    _window->draw(_sprite);

    for (auto& particle : particles)
    {
        particle->render();
    }
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

void Ball::triggerParticles()
{
    for (int i = 0; i < 10; ++i)
    {
        std::unique_ptr<ExplodeParticle> particle = std::make_unique<ExplodeParticle>(_window);
        particle->setPosition(_sprite.getPosition());

        particles.emplace_back(std::move(particle));
    }
}

sf::Vector2f Ball::getPosition(bool centre)
{
    if (!centre)
    {
        return _sprite.getPosition();
    }
    else
    {
        sf::Vector2f position{ _sprite.getPosition() };
        position.x += _sprite.getGlobalBounds().width;
        position.y += _sprite.getGlobalBounds().height;
        return position;
    }
}
