#include "PowerupFrenzy.h"


PowerupFrenzy::PowerupFrenzy(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : PowerupBase(window, paddle, ball)
{
    _sprite.setFillColor(frenzyEffectsColour);
}

PowerupFrenzy::~PowerupFrenzy()
{
}

std::pair<POWERUPS, float> PowerupFrenzy::applyEffect()
{
    //set the duration of the frenzy ball when the effect is applied
    _ball->setFrenzyBall(5.0f);
    return { frenzyBall, 5.0f };
}