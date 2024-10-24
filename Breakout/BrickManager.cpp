#include "BrickManager.h"
#include "GameManager.h"

namespace BrickManagerPrivate
{
    const int MAX_BRICK_HEALTH = 3;
    const int MIN_BRICK_HEALTH = 1;
    int generateRandomHealth() { return rand() % (MAX_BRICK_HEALTH + 1 - MIN_BRICK_HEALTH) + MIN_BRICK_HEALTH; }
}

BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{
    _brickTexture.loadFromFile("images/cabinetman.jpg");
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
            //int randomHealth = rand() % ( 1 - 5 + 1) +1;
            _bricks.emplace_back(x, y, brickWidth, brickHeight, &_brickTexture, BrickManagerPrivate::generateRandomHealth());
        }
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        if (brick.isDestroyed())
        {
            break;
        }

        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto brickIterator = _bricks.begin(); brickIterator != _bricks.end(); ++brickIterator) {
        if (!brickIterator->getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.
        if (brickIterator->isDestroyed())
        {
            //we know that the rest of the bricks are destroyed
            return 0;
        }

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brickIterator->getBounds();

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        if (brickIterator->getHealth() <= BrickManagerPrivate::MIN_BRICK_HEALTH)
        {
            brickIterator->destroy();
            std::rotate(brickIterator, brickIterator + 1, _bricks.end());
        }
        else
        {
            brickIterator->loseHealth(1);
        }

        _gameManager->addScore(1);
        break;
    }

    if (_bricks.begin()->isDestroyed())
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}
