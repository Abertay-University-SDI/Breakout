#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing, int level);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);
    void update(float dt);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;
    sf::Texture _brickTexture;

    //sound additions
    sf::SoundBuffer _popBuffer;
    sf::Sound* _popSound;
    float _randPitch = 1;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;
};
