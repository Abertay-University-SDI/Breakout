#include "Bullet.h"
#include "GameManager.h" // avoid cicular dependencies

Bullet::Bullet(sf::RenderWindow* window, float velocity, GameManager* gameManager)
    : _window(window), _velocity(velocity), _gameManager(gameManager), _direction({ 0,1 }), _isDestroyed(true)
{
    _sprite.setFillColor(sf::Color::Red);
    _sprite.setPosition(0, 0);
    _sprite.setSize(sf::Vector2f(5.f, 10.f));
}

Bullet::~Bullet()
{
}

void Bullet::render()
{
    if (!_isDestroyed) {
        _window->draw(_sprite);
    }
}


void Bullet::update(float dt)
{
    if (!_isDestroyed) {
        _sprite.move(_direction * _velocity * dt);

        // check bounds and bounce
        sf::Vector2f position = _sprite.getPosition();
        sf::Vector2u windowDimensions = _window->getSize();

        // Hit bottem of screen
        if (position.y > windowDimensions.y)
        {
            _isDestroyed = true;
        }

        // collision with paddle
        if (_sprite.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
        {
            _gameManager->getPaddle()->stun(0.75f);
        }
    }

}

void Bullet::setPosition(sf::Vector2f position)
{
    _sprite.setPosition(position.x, position.y);
    _isDestroyed = false;
}