#include "BrickManager.h"
#include "GameManager.h"
#include <iostream>

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

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;

            int positionFactor = i * cols + j;

            bool hasEyes = ((rand() + positionFactor) % 12 == 0);

            _bricks.emplace_back(x, y, brickWidth, brickHeight, hasEyes);
        }
    }
}

void BrickManager::createBossBrick()
{
    _bricks.clear();
    float brickWidth = 300.0f;
    float brickHeight = 100.0f;
    float x = (_window->getSize().x - brickWidth) / 2.0f;
    float y = TOP_PADDING;
    _bricks.emplace_back(x, y, brickWidth, brickHeight, true, true, 5);
    std::cout << "Boss created, health: " << _bricks.back().getHealth() << "\n";
}

void BrickManager::update(float dt)
{
    for (auto& brick : _bricks)
    {
        brick.update(dt);
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks)
    {
        brick.render(*_window);
    }
}

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction)
{
    int collisionResponse = 0;  
    for (auto& brick : _bricks)
    {
        if (brick.isDestroyed()) continue;
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue; 

        std::cout << "Collision detected with brick, isBoss: " << brick.isBoss() << "\n";

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // Determine collision direction
        collisionResponse = 2;  // Default vertical (top/bottom)
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
        {
            collisionResponse = 1;  // Horizontal (sides)
            std::cout << "Horizontal collision (sides)\n";
        }
        else
        {
            std::cout << "Vertical collision (top/bottom)\n";
        }

        brick.takeDamage();

        float offset = ball.getGlobalBounds().width + 10.f;  
        if (collisionResponse == 1)
        {
            if (ballPosition.x < brickBounds.left + brickBounds.width / 2)
            {
                ball.setPosition(brickBounds.left - offset, ballPosition.y); 
            }
            else
            {
                ball.setPosition(brickBounds.left + brickBounds.width + offset, ballPosition.y);  
            }
        }

        else
        {
            if (ballPosition.y < brickBounds.top + brickBounds.height / 2)
            {
                ball.setPosition(ballPosition.x, brickBounds.top - offset); 
            }
            else
            {
                ball.setPosition(ballPosition.x, brickBounds.top + brickBounds.height + offset); 
            }
        }

        if (brick.isDestroyed())
        {
            if (brick.hasEyes())
            {
                _gameManager->enterFrenzy();
            }
            if (brick.isBoss())
            {
                _gameManager->levelComplete();
            }
        }
        _gameManager->triggerShake(0.2f, 4.0f);
        _gameManager->playBrickHitSound(); 
        break;
    }

    brickCleanup();

    bool allBricksDestroyed = true;
    for (auto& brick : _bricks)
    {
        if (!brick.isDestroyed())
        {
            allBricksDestroyed = false;
            break;
        }
    }

    if (allBricksDestroyed && !_gameManager->isBossLevel())
    {
        _gameManager->levelComplete();
    }

    return collisionResponse;
}

void BrickManager::brickCleanup()
{
    for (auto it = _bricks.begin(); it != _bricks.end(); )
    {
        if (it->isDestroyed())
        {
            it = _bricks.erase(it);
        }
        else
        {
            ++it;
        }
    }
}