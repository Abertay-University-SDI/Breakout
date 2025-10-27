#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, sf::Texture* brickNormalTex, sf::Texture* brickStrongTex, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::Sprite& ball, sf::Vector2f& direction, bool isfireBall);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    GameManager* _gameManager;
    sf::Texture* _brickNormalTex;
    sf::Texture* _brickStrongTex;
    static constexpr float TOP_PADDING = 100.0f;
    static constexpr int STRONG_BRICK_CHANCE = 6;
};
