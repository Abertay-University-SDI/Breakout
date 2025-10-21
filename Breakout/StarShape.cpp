#include "StarShape.h"

StarShape::StarShape(int points, float innerRadius, float outerRadius) : _points(points), _innerRadius(innerRadius), _outerRadius(outerRadius) {
    update();
}

void StarShape::setInnerRadius(float radius) {
    _innerRadius = radius;
    update();
}

void StarShape::setOuterRadius(float radius) {
    _outerRadius = radius;
    update();
}

std::size_t StarShape::getPointCount() const {
    return _points * 2;
}

sf::Vector2f StarShape::getPoint(std::size_t index) const {
    float radius = (index % 2 == 0) ? _innerRadius : _outerRadius;
    float radians = index / (float) getPointCount() * 2.0f * 3.1415926535f;
    return sf::Vector2f(std::cos(radians), std::sin(radians)) * radius;
}