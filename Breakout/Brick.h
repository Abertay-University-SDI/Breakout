#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    // starting the fade vfx
    void burnOutBrick();
    // getters & setters for ball status
    bool isBrickDestroyed();
    void setIsDestroyed(bool isDestroyed);
    bool isDestructing = false;

private:
    sf::RectangleShape _shape;
    bool _isDestroyed;
    // variables for time based vfx
    sf::Clock _timer;
    bool _timerActivated = false;
    int _vfxTime = 200;
    int _startAplha = 255;
    int _endAlpha = 0;
};