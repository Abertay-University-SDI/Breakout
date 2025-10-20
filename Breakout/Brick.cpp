#include "Brick.h"

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
    }
    else {
        
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

// vfx that will fadout out brick when collided with fireball
// interpolates from opaque to transparent, then sets flag for deletion
// called on render cycle when flag is set
void Brick::burnOutBrick() {
    if (!_timerActivated && !_isDestroyed) {
        _timer.restart();
        _timerActivated = true;
    }
    else {

        int currentTime = _timer.getElapsedTime().asMilliseconds();
        int currentAlpha = _endAlpha;
        if (currentTime >= _vfxTime) {
            _isDestroyed = true;
        }
        else {
            currentAlpha = _startAplha + (_endAlpha - _startAplha) * currentTime / _vfxTime;
            _shape.setFillColor(sf::Color(255, 0, 0, currentAlpha));
        }
    }
    
}

bool Brick::isBrickDestroyed() {
    return _isDestroyed;
}

void Brick::setIsDestroyed(bool isdestroyed) {
    _isDestroyed = isdestroyed;
}