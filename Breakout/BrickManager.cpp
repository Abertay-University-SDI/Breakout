#include "BrickManager.h"
#include "GameManager.h"

BrickManager::BrickManager(sf::RenderWindow* window, sf::Texture* brickNormalTex, sf::Texture* brickStrongTex, GameManager* gameManager)
    : _window(window), _brickNormalTex(brickNormalTex), _brickStrongTex(brickStrongTex), _gameManager(gameManager)
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
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            // 1 / [STRONG_BRICK_CHANCE] chance of being a strong brick (takes 2 hits)
            bool isStrong = rand() % STRONG_BRICK_CHANCE == 0;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, isStrong, _brickNormalTex, _brickStrongTex);
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::Sprite& ball, sf::Vector2f& direction, bool isfireBall)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.

    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;
        
        // if strong (and ball isn't not fireball), make weak then continue to next brick
        if (brick.getIsStrong() && !isfireBall)
        {
            brick.setIsStrong(false);
            continue;
        }

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        brick = _bricks.back();
        _bricks.pop_back();
        break;
    }

    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}