#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <random>
#include "ExtraLife.h" 


class ExtraLivesManager
{
public:
    ExtraLivesManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gamemanager);
    ~ExtraLivesManager();

    void update(float dt);
    void render();
    void spawnExtraLife(sf::Vector2f x); // Method to spawn an extra life
    bool checkCollision(ExtraLife* extralife); // Check collision with paddle
    int getLivesSpawned();

private:
    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    GameManager* _gameManager;
    std::vector<ExtraLife*> _extraLives;            // used to manage deletion.
    std::mt19937 _rng; // mersenne twister

};


