#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
    Brick(float x, float y, float width, float height, int hitPoints);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
	void hit();
	int getHitPoints() const;
	void setColor(const sf::Color& color) { _shape.setFillColor(color); _color = color; }
private:
    sf::RectangleShape _shape;
	int _hitPoints =0;
	sf::Color _color;
    bool _isDestroyed;
};