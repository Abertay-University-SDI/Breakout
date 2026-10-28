#include "Brick.h"
#include "GameManager.h" // avoid cicular dependencies

Brick::Brick(float x, float y, float width, float height, sf::RenderWindow* window, float velocity, GameManager* gameManager, sf::Vector2f direction, sf::Color color)
    : _window(window), _velocity(velocity), _gameManager(gameManager), _direction(direction), _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(color);
    _bulletCooldown = rand() % 5 + 0.5;
}

void Brick::render()
{
    if (!_isDestroyed) {
        _window->draw(_shape);
    }
}

void Brick::update(float dt)
{
    if (!_isDestroyed) {

        if (_bulletCooldown > 0)
        {
            _bulletCooldown -= dt;
        }

        _shape.move(_direction * _velocity * dt);

        // check bounds and bounce
        sf::FloatRect bounds = _shape.getGlobalBounds();
        sf::Vector2f position = _shape.getPosition();
        sf::Vector2u windowDimensions = _window->getSize();


        // bounce on walls
        if ((position.x >= windowDimensions.x - 2 * (bounds.width / 2) && _direction.x > 0) || (position.x <= 0 && _direction.x < 0))
        {
            _direction.x *= -1;
        }

        // bounce floor
        if (position.y > windowDimensions.y)
        {
			_isDestroyed = true;
            _gameManager->loseLife();
        }

        // collision with paddle
        if (_shape.getGlobalBounds().intersects(_gameManager->getPaddle()->getBounds()))
        {
            _isDestroyed = true;
            _gameManager->getPaddle()->stun(1.f);
        }
    }
}


sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}


sf::Vector2f Brick::getMiddle()
{
    sf::FloatRect bounds = _shape.getGlobalBounds();
    return sf::Vector2f(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

}