#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <cmath>

// Outline from https://www.sfml-dev.org/tutorials/3.0/graphics/shape/#custom-shape-types
// But that was for an ellipse, so I had to adapt it to make a star

class StarShape : public sf::Shape {
public:
    explicit StarShape(int points, float innerRadius, float outerRadius);
    void setInnerRadius(float radius);
    void setOuterRadius(float radius);
    std::size_t getPointCount() const override;
    sf::Vector2f getPoint(std::size_t index) const override;
private:
    int _points;
    float _innerRadius;
    float _outerRadius;
};