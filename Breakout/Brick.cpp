#include "Brick.h"

Brick::Brick(float x, float y, float width, float height, bool isStrong, sf::Texture* brickNormalTex, sf::Texture* brickStrongTex)
    : _isDestroyed(false), _isStrong(isStrong), _brickNormalTex(brickNormalTex), _brickStrongTex(brickStrongTex)
{
    _sprite.setPosition(x, y);
    _sprite.setTexture(isStrong ? *brickStrongTex : *brickNormalTex);
    _sprite.setScale(sf::Vector2f(width / _sprite.getTexture()->getSize().x, height / _sprite.getTexture()->getSize().y));
}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_sprite);
    }
}

sf::FloatRect Brick::getBounds() const
{
    return _sprite.getGlobalBounds();
}

bool Brick::getIsStrong() const
{
    return _isStrong;
}

void Brick::setIsStrong(bool b)
{
    _isStrong = b;
    _sprite.setTexture(_isStrong ? *_brickStrongTex : *_brickNormalTex);
}
