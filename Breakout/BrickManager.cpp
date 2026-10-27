#include "BrickManager.h"
#include "GameManager.h"
#include <algorithm>

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
}

void BrickManager::createBricks(int rows, int cols, float brickWidth, float brickHeight, float spacing)
{
    float leftEdge;
    if (cols % 2 == 0) 
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f) * brickWidth + (cols / 2.0f - 0.5f) * spacing);
    else
        leftEdge = _window->getSize().x / 2 - ((cols / 2.0f - 0.5f) * brickWidth + (cols / 2.0f) * spacing);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + BRICK_TOP_PADDING;
            _bricks.emplace_back(x, y, brickWidth, brickHeight);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    float radius = ball.getRadius();
    sf::Vector2f ballCentre = ball.getPosition() + sf::Vector2f(radius, radius);

    auto isHit = [&](const Brick& brick) {
        sf::FloatRect bounds = brick.getBounds();
        float nearestX = std::clamp(ballCentre.x, bounds.left, bounds.left + bounds.width);
        float nearestY = std::clamp(ballCentre.y, bounds.top, bounds.top + bounds.height);
        float dx = ballCentre.x - nearestX;
        float dy = ballCentre.y - nearestY;
        if (dx * dx + dy * dy > radius * radius) return false;

        if (collisionResponse == 0)
        {
            collisionResponse = 2;
            if (ballCentre.y > bounds.top && ballCentre.y < bounds.top + bounds.height)
                collisionResponse = 1;
        }
        return true;
    };

    _bricks.erase(std::remove_if(_bricks.begin(), _bricks.end(), isHit), _bricks.end());

    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}