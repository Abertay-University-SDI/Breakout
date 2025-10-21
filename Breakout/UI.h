#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "PowerupManager.h"
#include "Ball.h"

class GameManager;

class UI {
public:
    UI(sf::RenderWindow* window, int lives, GameManager* gameManager, Ball* ball);
    ~UI();

    void updatePowerupText(std::pair<POWERUPS, float>);
    void lifeLost(int lives);
    void render();

private:
    GameManager* _gameManager;
    Ball* _ball;

    sf::RenderWindow* _window;
    sf::Font _font;
    sf::Text _powerupText;
    std::vector<sf::CircleShape> _lives;

    sf::RectangleShape _progressBar;
    sf::RectangleShape _progressBarBackground;
    float _initialPowerupDuration;
    bool _showProgressBar; 

    static constexpr float LIFE_RADIUS = 15.0f;
    static constexpr float LIFE_PADDING = 20.0f;
    static constexpr float PROGRESS_BAR_WIDTH = 100.0f;
    static constexpr float PROGRESS_BAR_HEIGHT = 10.0f;
    static constexpr float PROGRESS_BAR_Y_OFFSET = 30.0f;
    static constexpr float TEXT_Y_OFFSET = 40.0f;
};