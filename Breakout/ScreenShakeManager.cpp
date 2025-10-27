#include "ScreenShakeManager.h"

ScreenShakeManager::ScreenShakeManager(sf::RenderWindow* window)
: _window(window)
{

}

// set screenshake parameters upon call to do a screenshake with said parameters
void ScreenShakeManager::shake(float range, float duration)
{
    _shakeDuration = duration;
    _shakeTimer = duration;
    _shakeRangeModifier = range;
}

// update screenshake camera offset (_camOffset)
// randomised offset within a +/- _shakeRangeModifier range, with the range decreasing overtime
void ScreenShakeManager::update(float dt)
{
    if (_shakeTimer > 0)
    {
        _shakeTimer -= dt;
        if (_shakeTimer <= 0)
            _shakeTimer = 0;

        float shakeRange = _shakeRangeModifier * (_shakeTimer / _shakeDuration);
        
        // rand range between -1 to 1

        _camOffset = sf::Vector2f(shakeRange * std::sin(_shakeTimer * _shakeSpinSpeed), shakeRange * std::cos(_shakeTimer * _shakeSpinSpeed));
    }
}

// update view centre position based on _camOffset
void ScreenShakeManager::render()
{
    sf::Vector2f viewSize = _window->getView().getSize();
    sf::View view = _window->getView();
    view.setCenter(viewSize.x / 2 + _camOffset.x, viewSize.y / 2 + _camOffset.y);
    _window->setView(view);
}