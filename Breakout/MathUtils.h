#pragma once

#include "SFML/System/Vector2.hpp"
#include <math.h>

namespace MathUtils
{
    static float getLength(const sf::Vector2f& vec)
    {
        return sqrt((vec.x * vec.x) + (vec.y * vec.y));
    }

    static bool normalize(sf::Vector2f& vec)
    {
        float length = getLength(vec);
        if (length != 0)
        {
            vec = sf::Vector2f(vec.x / length, vec.y / length);
            return true;
        }
        else
            return false;
    }

    static sf::Vector2f multiplyVF(const sf::Vector2f& vec, float a)
    {
        return sf::Vector2f(vec.x * a, vec.y * a);
    }

    template<typename T>
    static T lerp(T a, T b, float time)
    {
        return ((1 - time) * a) + (time * b);
    }
}