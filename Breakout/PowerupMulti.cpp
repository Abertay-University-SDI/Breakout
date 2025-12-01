#include "PowerupMulti.h"

PowerupMulti::PowerupMulti(sf::RenderWindow* window, Paddle* paddle, Ball* ball, std::vector<POWERUPS> givenPowers)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(ballEffectsColour);
    powers = givenPowers;
    isMulti = true;
}

PowerupMulti::~PowerupMulti()
{
}

std::pair<POWERUPS, float> PowerupMulti::applyEffect()
{
    return std::pair<POWERUPS, float>();
}

POWERUPS PowerupMulti::checkEffect()
{
    return POWERUPS();
}

std::pair<POWERUPS, float> PowerupMulti::applyMulti(int index)
{
    

    switch (powers[index]) //The higher maxPowerupsAtOnce is, the higher chance of adding an extra powerup 
    {
    case slowBall:
        _ball->changeVelocity(0.5f, 5.0f);
        break;
    case fastBall:
        _ball->changeVelocity(2.f, 5.0f);
        break;
    case fireBall:
        _ball->setFireBall(5.0f);
        break;
    case bigPaddle:
        _paddle->changeWidth(1.5f, 5.0f);
        break;
    case smallPaddle:
        _paddle->changeWidth(0.67f, 5.0f);
        break;
    }

    return { powers[index], 5.0f };
}

POWERUPS PowerupMulti::checkMulti(int index)
{
    return powers[index];
}
