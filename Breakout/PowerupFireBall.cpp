#include "PowerupFireBall.h"


PowerupFireBall::PowerupFireBall(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos)
    : PowerupBase(window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
    _colour = ballEffectsColour;
}

PowerupFireBall::~PowerupFireBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }


    
}

std::tuple<POWERUPS, float, sf::Color> PowerupFireBall::applyEffect()
{
    for (int i = 0; i < _balls.size(); i++)
    {
        _balls[i]->setFireBall(5.0f);
    }
    return { fireBall, 5.0f, _colour };
}