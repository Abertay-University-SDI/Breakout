#pragma once
#include "GameManager.h"
#include "PowerupBase.h"
class PowerupMultiBall : public PowerupBase
{
public:
    PowerupMultiBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gameManager);
    ~PowerupMultiBall();
    GameManager* game_Manager;
    std::pair<POWERUPS, float> applyEffect() override; // Method to apply the power-up effect


};

