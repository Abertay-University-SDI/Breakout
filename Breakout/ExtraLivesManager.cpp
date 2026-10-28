#include "ExtraLivesManager.h"
#include "GameManager.h"

ExtraLivesManager::ExtraLivesManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball, GameManager* gamemanager)
{
    _window = window;
    _paddle = paddle;
    _ball = ball;
    _gameManager = gamemanager;
}

ExtraLivesManager::~ExtraLivesManager()
{
    for (auto life : _extraLives)
    {
        delete life;
    }
    _extraLives.clear();
}

void ExtraLivesManager::update(float dt)
{

    for (auto it = _extraLives.begin(); it != _extraLives.end(); )
    { 
        if (checkCollision(*it))
            _gameManager->addLife();

        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _extraLives.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void ExtraLivesManager::render()
{
    for (auto& powerup : _extraLives)
    {
        powerup->render();
    }
}

void ExtraLivesManager::spawnExtraLife(sf::Vector2f x)
{

    std::uniform_real_distribution<float> xDist(
        _window->getSize().x * 0.05f,
        _window->getSize().x * 0.95f
    );

    //float spawnX = xDist(_rng);
    sf::Vector2f spawnX = x;

    _extraLives.push_back(new ExtraLife(_window, _paddle, _ball, spawnX, _gameManager));

}

bool ExtraLivesManager::checkCollision(ExtraLife* extralife)
{
        if (extralife->checkCollisionWithPaddle())
        {
            //Add Life 
            extralife->setAlive(false);
            return true;
        }
    return false;
}

int ExtraLivesManager::getLivesSpawned()
{
    return _extraLives.size();
}
