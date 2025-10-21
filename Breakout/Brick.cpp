#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, bool hasEyes, bool isBoss, int health)
    : _isDestroyed(false), _hasEyes(hasEyes), _isBoss(isBoss), _bossHealth(health), _hitColorTimer(0.f)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(_isBoss ? sf::Color::Blue : sf::Color::Blue);
    _bossVelocity = _isBoss ? sf::Vector2f(100.f, 0.f) : sf::Vector2f(0.f, 0.f);
}

void Brick::update(float dt)
{
    if (_isBoss && !_isDestroyed)
    {
        sf::Vector2f position = _shape.getPosition();
        position += _bossVelocity * dt;
        if (position.x <= 0 || position.x + _shape.getSize().x >= WINDOW_WIDTH)
        {
            _bossVelocity.x = -_bossVelocity.x;
        }
        _shape.setPosition(position);

        if (_hitColorTimer > 0.f)
        {
            _hitColorTimer -= dt;
            if (_hitColorTimer <= 0.f)
            {
                //revert to boss to blue
                _shape.setFillColor(sf::Color::Blue); 
            }
        }
    }
}

void Brick::takeDamage()
{
    if (_isBoss)
    {
        _bossHealth--;
        if (_bossHealth <= 0)
        {
            _isDestroyed = true;
        }
        else
        {
            //set to darker red when hit
            _shape.setFillColor(sf::Color(139, 0, 0)); 
            _hitColorTimer = 0.25f; 
        }
    }
    else
    {
        _isDestroyed = true;
    }
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed)
    {
        window.draw(_shape);

        if (_hasEyes)
        {
            //bigger eyes for boss, smaller eyes for bricks
            float eyeSize = _isBoss ? 40.f : 5.f; 
            float pupilSize = _isBoss ? 20.f : 3.f;
            float eyeOffsetX = _isBoss ? 0.20f : 0.25f; 
            float eyeOffsetY = 0.45f;

            sf::CircleShape leftEye(eyeSize);
            leftEye.setFillColor(sf::Color::White);
            leftEye.setPosition(_shape.getPosition().x + _shape.getSize().x * eyeOffsetX - eyeSize, _shape.getPosition().y + _shape.getSize().y * eyeOffsetY - eyeSize);
            window.draw(leftEye);

            sf::CircleShape leftPupil(pupilSize);
            leftPupil.setFillColor(sf::Color::Black);
            leftPupil.setPosition(_shape.getPosition().x + _shape.getSize().x * eyeOffsetX - pupilSize, _shape.getPosition().y + _shape.getSize().y * eyeOffsetY);
            window.draw(leftPupil);

            sf::CircleShape rightEye(eyeSize);
            rightEye.setFillColor(sf::Color::White);
            rightEye.setPosition(_shape.getPosition().x + _shape.getSize().x * (1.0f - eyeOffsetX) - eyeSize, _shape.getPosition().y + _shape.getSize().y * eyeOffsetY - eyeSize);
            window.draw(rightEye);

            sf::CircleShape rightPupil(pupilSize);
            rightPupil.setFillColor(sf::Color::Black);
            rightPupil.setPosition(_shape.getPosition().x + _shape.getSize().x * (1.0f - eyeOffsetX) - pupilSize, _shape.getPosition().y + _shape.getSize().y * eyeOffsetY);
            window.draw(rightPupil);
        }

        if (_isBoss)
        {
            sf::RectangleShape healthBarBack(sf::Vector2f(_shape.getSize().x, 5));
            healthBarBack.setFillColor(sf::Color::Black);
            healthBarBack.setPosition(_shape.getPosition().x, _shape.getPosition().y - 10);
            window.draw(healthBarBack);
            float healthRatio = static_cast<float>(_bossHealth) / 5.0f;
            sf::RectangleShape healthBarFront(sf::Vector2f(_shape.getSize().x * healthRatio, 5));
            healthBarFront.setFillColor(sf::Color::Red);
            healthBarFront.setPosition(_shape.getPosition().x, _shape.getPosition().y - 10);
            window.draw(healthBarFront);
        }
    }
}

void Brick::setEyes(bool hasEyes)
{
    _hasEyes = hasEyes;
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

void Brick::setDestroyed(bool isDestroyed)
{
    _isDestroyed = isDestroyed;
}

bool Brick::isDestroyed() const
{
    return _isDestroyed;
}

bool Brick::hasEyes() const
{
    return _hasEyes;
}

bool Brick::isBoss() const
{
    return _isBoss;
}

int Brick::getHealth() const
{
    return _bossHealth;
}