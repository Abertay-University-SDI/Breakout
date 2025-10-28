#include "Brick.h"
#include <iostream>

Brick::Brick(float x, float y, float width, float height)
    : _isDestroyed(false)
{
    _shape.setPosition(x, y);
    _shape.setSize(sf::Vector2f(width, height));
    _shape.setFillColor(sf::Color::Red);

    _isDamaged = false;


    //_texture.loadFromFile("assets/SolidTexture.png");
    //_brokenTexture.loadFromFile("assets/CrackedTexture.png");

    //if (!_texture.loadFromFile("assets/CrackedTexture.png"))
    //{
    //    std::cerr << "Warning: Couldn't load solid texture." << std::endl;
    //}

    //if (!_brokenTexture.loadFromFile("assets/CrackedTexture.png"))
    //{
    //    std::cerr << "Warning: Couldn't load solid texture." << std::endl;
    //}

}

void Brick::render(sf::RenderWindow& window)
{
    if (!_isDestroyed) {
        window.draw(_shape);
    }

    if (_isDamaged)
    {
        _shape.setFillColor(sf::Color::Yellow);
    }



    //if (!_isDestroyed && !_isDamaged)   // If not destroyed or damaged
    //{
    //    //_shape.setTexture(&_texture);
    //    //_shape.setFillColor(sf::Color::White);
    //    window.draw(_shape);
    //}

    //if (!_isDestroyed && _isDamaged)    // If not destroyed but damaged
    //{
    //    //_shape.setTexture(&_brokenTexture);
    //    _shape.setFillColor(sf::Color::Black);
    //    window.draw(_shape);
    //}


}

sf::FloatRect Brick::getBounds() const
{
    return _shape.getGlobalBounds();
}

