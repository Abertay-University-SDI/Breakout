#include "BrickManager.h"
#include "GameManager.h"



BrickManager::BrickManager(sf::RenderWindow* window, GameManager* gameManager)
    : _window(window), _gameManager(gameManager)
{

    buffer.loadFromFile("sfx/brick_destroyed.mp3");
    sound.setBuffer(buffer);
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
            _bricks.emplace_back(x, y, brickWidth, brickHeight, 1+i); //bricks get stronger the closer they are, 1 hp minimum
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
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        brick.decrease_health(); //reduce health on hit
        
        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector

        if (brick.get_health() <= 0)
        {
            brick = _bricks.back();
            _bricks.pop_back();

            sound.play();
        }
        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}

bool BrickManager::checkPointCollision(sf::Vector2f point)
{
    bool collision_response = false;

    for (auto& brick : _bricks) {
        if (!brick.getBounds().contains(point)) continue;

        brick.decrease_health();
        if (brick.get_health() <= 0)
        {
            brick = _bricks.back();
            _bricks.pop_back();

            sound.play();
        }

        collision_response = true;

        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }

    return collision_response;
}

void BrickManager::update(float dt)
{
    for (auto& brick : _bricks) {
        brick.update_hit_time(dt);
    }

}
