#include "PowerupSlowBall.h"


PowerupSlowBall::PowerupSlowBall(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos)
    : PowerupBase(window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour); 
    _colour = ballEffectsColour;
}

PowerupSlowBall::~PowerupSlowBall()
{
}

std::tuple<POWERUPS, float, sf::Color> PowerupSlowBall::applyEffect()
{
    for (int i = 0; i < _balls.size(); i++)
    {
        _balls[i]->setVelocity(0.5f, 5.0f);
    }

    return { slowBall, 5.0f, _colour };
}