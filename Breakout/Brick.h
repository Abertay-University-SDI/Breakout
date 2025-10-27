#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, bool isStrong, sf::Texture* brickNormalTex, sf::Texture* brickStrongTex);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool getIsStrong() const;
    void setIsStrong(bool b);

private:
    sf::Sprite _sprite;

    sf::Texture* _brickNormalTex;
    sf::Texture* _brickStrongTex;

    bool _isDestroyed;
    bool _isStrong;
};