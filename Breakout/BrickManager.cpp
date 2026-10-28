#include "BrickManager.h"
#include "GameManager.h"

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

        float velocity = 20.f;
        sf::Vector2f direction = sf::Vector2f(1.f, 0.1f);
        sf::Color  color = sf::Color{ 255, 0, 0 };

        if (i == 4)
        {
            color = sf::Color{ 255, 255, 0 };
        }
        else if (i == 3)
        {
            direction = sf::Vector2f(-1.f, 0.2f);
            color = sf::Color{ 255, 175, 0 };
        }
        else if (i == 2)
        {
            velocity = 30.f;
            color = sf::Color{ 255, 100, 0 };
        }
        else if (i == 1)
        {
			velocity = 40.f;
            direction = sf::Vector2f(-1.f, 0.2f);
            color = sf::Color{ 255, 50, 0 };
        }

        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
            if (i % 2 == 0)
            {
                _bricks.emplace_back(x, y + (j * 5), brickWidth, brickHeight, _window, velocity, _gameManager, direction, color);
            }
            else
            {
                _bricks.emplace_back(x, y - (j * 5), brickWidth, brickHeight, _window, velocity, _gameManager, direction, color);
            }
        }
    }

    for (int i = 0; i < 25; i++)
    {
        _bullets.emplace_back(_window, 400.f, _gameManager);
    }
}

void BrickManager::render()
{
    for (auto& brick : _bricks) {
        brick.render();
    }

    for (auto& bullet : _bullets) {
        bullet.render();
    }
}

void BrickManager::update(float dt)
{
    for (auto& brick : _bricks) {
        brick.update(dt);
    }

    for (auto& bullet : _bullets) {
        bullet.update(dt);
    }

    for (auto& brick : _bricks) {

        if (brick._bulletCooldown <= 0)
        {
            int chance = rand() % 100 + 1;
            if (chance < 30 - (_bricks.size()/2))
            {
                for (auto& bullet : _bullets) {
                    if (bullet._isDestroyed)
                    {
                        bullet.setPosition(brick.getMiddle());
                        break;
                    }
                }
            }
            brick._bulletCooldown = rand() % (_bricks.size()/10) + 1;
            
        }
       
    }

    for (auto brick = _bricks.begin(); brick != _bricks.end();)
    {
        if ((*brick)._isDestroyed)
            brick = _bricks.erase(brick);
        else
            brick++;
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

        // default vertical bounce (collision is top/bottom)
        collisionResponse = 2;
        if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;

        // Mark the brick as destroyed (for simplicity, let's just remove it from rendering)
        // In a complete implementation, you would set an _isDestroyed flag or remove it from the vector
        //brick = _bricks.back();
        //_bricks.pop_back();
		brick._isDestroyed = true;
        break;
    }
    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}