#pragma once
#include <vector>
#include "Brick.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction, Ball& col);
    void infectNearbyBricks(Brick& infect);
    void phaseThroughBricks(Brick& ghost);
    void damageBrick(Brick& brick);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
