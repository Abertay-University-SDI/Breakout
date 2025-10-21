#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class GameManager;

enum class BrickCollision {
    none,
    horizontal,
    vertical
};

class BrickManager {
public:
    BrickManager(GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render(sf::RenderWindow& window);
    BrickCollision checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

private:
    std::vector<Brick> _bricks;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
