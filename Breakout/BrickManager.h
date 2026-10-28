#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include "Explosion.h"

class GameManager;

class BrickManager {
public:
    //BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    float checkExplosionRadius(Explosion explosion);
    void destroyBricks();
    void update();

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;

    Explosion _explosion;
    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
