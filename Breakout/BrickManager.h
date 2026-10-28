#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacingWidth, float spacingHeight);
    void update(float dt);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

    void setParameters(float s, float h, float a);
private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;

    float _brickSpeed = 0;
    float _lapHeightDecrease = 0;
    float _brickAcceleration = 0;
    bool _movingLeft = false;
};
