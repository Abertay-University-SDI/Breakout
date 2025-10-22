#pragma once
#include <vector>
#include "Brick.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Hitmarker.h"

class GameManager;

class BrickManager {
public:
    BrickManager(sf::RenderWindow* window, GameManager* gameManager);
    void createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing);
    void render();
    int checkCollision(sf::CircleShape& ball, sf::Vector2f& direction);

private:
    std::vector<Brick> _bricks;
    sf::RenderWindow* _window;


    sf::Font _font;

    GameManager* _gameManager;
    static constexpr float TOP_PADDING = 100.0f;

    // ---- Audio ---- //
    sf::SoundBuffer buffer;
    sf::Sound hit;

    // ----- VFX ----- // 
    std::vector<Hitmarker> Hitmarkers;
};
