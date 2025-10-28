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
        for (int j = 0; j < cols; ++j) {
            float x = j * (brickWidth + spacing) + leftEdge;
            float y = i * (brickHeight + spacing) + TOP_PADDING;
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

int BrickManager::checkCollision(sf::CircleShape& ball, sf::Vector2f& direction, Ball& col)
{
    //if (col.isPhantomBall()) return 0;

    int collisionResponse = 0;  // set to 1 for horizontal collision and 2 for vertical.
    for (auto& brick : _bricks) {
        if (!brick.getBounds().intersects(ball.getGlobalBounds())) continue;    // no collision, skip.

        sf::Vector2f ballPosition = ball.getPosition();
        float ballY = ballPosition.y + 0.5f * ball.getGlobalBounds().height;
        sf::FloatRect brickBounds = brick.getBounds();

        // Skip bounce if phantom
        if (!col.isPhantomBall())
        {
            // default vertical bounce (collision is top/bottom)
            collisionResponse = 2;
            if (ballY > brickBounds.top && ballY < brickBounds.top + brickBounds.height)
            // unless it's horizontal (collision from side)
            collisionResponse = 1;
        }

        // Phantom is too much like fireball but without bounce, possibly only allow it to damage blocks



        //// If brick is damaged, destroy brick
        //if (brick.isDamaged())  
        //{
        //    brick = _bricks.back();
        //    _bricks.pop_back();
        //    break;
        //}

        //// If brick is undamaged, damage brick
        //else
        //{
        //    brick.setDamaged(true);
        //}

        //// If brick is undamaged and the ball isnt a fireball, damage on contact
        //if (!brick.isDamaged() && !col.isFireBall())
        //{
        //    brick.setDamaged(true);
        //}
        //else if (col.isInfBall())
        //{
        //    brick.setDamaged(true);
        //    infectNearbyBricks(brick);
        //    break;
        //}
        //// If brick is damaged or the ball is on fire, destroy on contact
        //else
        //{
        //    brick = _bricks.back();
        //    _bricks.pop_back();
        //    break;
        //}

        if (!col.isInfBall() && !col.isFireBall() && !col.isPhantomBall())
        {
            damageBrick(brick);
        }
        else if (col.isInfBall())
        {
            damageBrick(brick);
            infectNearbyBricks(brick);
        }
        else if (col.isFireBall())
        {
            brick = _bricks.back();
            _bricks.pop_back();
        }
        else if (col.isPhantomBall())
        {
            phaseThroughBricks(brick);
        }

    }

    if (_bricks.size() == 0)
    {
        _gameManager->levelComplete();
    }
    return collisionResponse;
}

void BrickManager::infectNearbyBricks(Brick& infected)
{
    const sf::FloatRect brickBounds = infected.getBounds();
    const float infectionRange = brickBounds.width * 2.f;

    for (auto& brick : _bricks)
    {
        if (&brick == &infected) continue;  // Skip infected brick

        sf::FloatRect bounds = brick.getBounds();

        bool getsInfected = std::abs(bounds.left - brickBounds.left) < infectionRange && std::abs(bounds.top - brickBounds.top) < brickBounds.height * 2.f;
    
        // If in infection range
        if (getsInfected && !brick.isDamaged())
        {
            damageBrick(brick);
        }
    }

}

// Pass through bricks, damaging them
void BrickManager::phaseThroughBricks(Brick& brick)
{
    if (!brick.isDamaged())
    {
        brick.setDamaged(true);
    }

}


void BrickManager::damageBrick(Brick& brick)
{
    // If damaged or using fireball, destroy
    if (brick.isDamaged())
    {
        brick = _bricks.back();
        _bricks.pop_back();
    }

    // Damage brick
    else if(!brick.isDamaged())
    {
        brick.setDamaged(true);
    }


}

