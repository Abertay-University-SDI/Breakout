#include "PowerupFastBall.h"

PowerupFastBall::PowerupFastBall(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos)
    : PowerupBase(window, paddle, balls, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
    _colour = ballEffectsColour;
}

PowerupFastBall::~PowerupFastBall()
{
}

std::tuple<POWERUPS, float, sf::Color> PowerupFastBall::applyEffect()
{
    for (int i = 0; i < _balls.size(); i++)
    {
        _balls[i]->setVelocity(2.f, 5.0f);
    }
    return { fastBall, 5.0f, _colour };
}