#include "PowerupMultiBall.h"

PowerupMultiBall::PowerupMultiBall(sf::RenderWindow* window, Paddle* paddle, std::vector<Ball*>& balls, float x_pos)
    : PowerupBase(window, paddle, balls, x_pos)
{
    _sprite.setFillColor(extraBallEffectsColour);
    _colour = extraBallEffectsColour;
}

PowerupMultiBall::~PowerupMultiBall()
{
}

std::tuple<POWERUPS, float, sf::Color> PowerupMultiBall::applyEffect()
{
    
    return { multiBall, 5.0f, _colour };
}