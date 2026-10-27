#include "PowerupMultiBall.h"


PowerupMultiBall::PowerupMultiBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos)
    : PowerupBase(window, paddle, ball, x_pos)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupMultiBall::~PowerupMultiBall()
{

    int* pInteger = new int();

    if (pInteger != nullptr)
    {
        // use my pointer to do things.
    }



}

std::pair<POWERUPS, float> PowerupMultiBall::applyEffect()
{
    _ball->setMultiBall(5.0f);
    return { multiBall, 5.0f };
}