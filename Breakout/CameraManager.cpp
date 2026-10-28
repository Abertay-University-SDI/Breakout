#include "CameraManager.h"
#include <ctime>
#include <cstdlib>

CameraManager::CameraManager(sf::RenderWindow* window)
    : _window()
{
    // Seed for random number
    srand(time(0));

    _window = window;
    _view = _window->getView();

    // Set the view center
    sf::Vector2u size = window->getSize();
    _center = sf::Vector2f(size.x / 2, size.y / 2);
    _view.setCenter(_center);
}

void CameraManager::update(float dt)
{
    // Generate a random number on update
    float randomNum = -1 + 2 * ((float)rand()) / RAND_MAX;

    // Set rotation angle
    double angle = 20.0f * _trauma * randomNum;

    // Set offset
    sf::Vector2f offset;
    offset.x = 15.0f * _trauma * randomNum;
    offset.y = 15.0f * _trauma * randomNum;

    // Apply changes to view
    _view.setRotation(angle);
    _view.setCenter(_center + offset);
    _window->setView(_view);


    // If shake's starting point is beyond its duration, then it won't shake
    if (_shakeStart >= _shakeDuration) {
        return;
    }

    // Shake start time takes from update
    _shakeStart += sf::seconds(dt);

    // Screen shake lasts only as long as the shake's duration
    float duration = _shakeStart / _shakeDuration;
    _trauma *= 1.0 - duration * duration; // ; Multipler amplifies the trauma just a bit more for more shake
}

void CameraManager::screenShake(float trauma, float duration_ms)
{
    _trauma += trauma; // Screen trauma based on trauma set in game manager

    _shakeDuration = sf::milliseconds(duration_ms); // Shake duration lasts set duration in game manager
    _shakeStart = sf::seconds(0); // Resets shake start when function is called
}
