#include "PowerupMultiBall.h"
#include "GameManager.h"

PowerupMultiBall::PowerupMultiBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gameManager)
    : PowerupBase(window, paddle, ball), game_Manager(gameManager)
{
    _sprite.setFillColor(ballEffectsColour);
}

PowerupMultiBall::~PowerupMultiBall()
{
}

std::pair<POWERUPS, float> PowerupMultiBall::applyEffect()
{
    game_Manager->spawnMultiballs();
    return { multiBall, 5.0f };
}