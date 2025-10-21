#include <sstream>
#include "UI.h"
#include "GameManager.h"
#include <iomanip>
#include <iostream>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager, Ball* ball)
    : _window(window), _gameManager(gameManager), _ball(ball), _initialPowerupDuration(0.f), _showProgressBar(false)
{
    for (int i = lives; i > 0; --i) {
        sf::CircleShape newLife;
        newLife.setFillColor(sf::Color::Red);
        newLife.setOutlineColor(sf::Color::Yellow);
        newLife.setOutlineThickness(4.0f);
        newLife.setRadius(LIFE_RADIUS);
        newLife.setPosition((LIFE_RADIUS * 2 + LIFE_PADDING) * i, LIFE_PADDING);
        _lives.push_back(newLife);
    }
    _powerupText.setCharacterSize(20);
    _powerupText.setFillColor(sf::Color::Cyan);
    _font.loadFromFile("font/menu_text.ttf");
    _powerupText.setFont(_font);

    _progressBar.setSize(sf::Vector2f(PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT));
    _progressBar.setFillColor(sf::Color::Transparent);

    _progressBarBackground.setSize(sf::Vector2f(PROGRESS_BAR_WIDTH, PROGRESS_BAR_HEIGHT));
    _progressBarBackground.setFillColor(sf::Color::Black);
    _progressBarBackground.setOutlineColor(sf::Color::White);
    _progressBarBackground.setOutlineThickness(1.0f);
}

UI::~UI() {}

void UI::updatePowerupText(std::pair<POWERUPS, float> powerup) {
    std::ostringstream oss;

    if (powerup.first == none) {
        _progressBar.setFillColor(sf::Color::Transparent);
        _progressBarBackground.setFillColor(sf::Color::Transparent);
        _initialPowerupDuration = 0.f;
        _powerupText.setString("");
        _showProgressBar = false;
        return;
    }

    _showProgressBar = true;

    if (_initialPowerupDuration == 0.f) {
        _initialPowerupDuration = powerup.second;
    }

    float progressRatio = powerup.second / _initialPowerupDuration;
    float barWidth = PROGRESS_BAR_WIDTH * progressRatio;
    _progressBar.setSize(sf::Vector2f(barWidth, PROGRESS_BAR_HEIGHT));

    float ballX = _ball->getPosition().x + _ball->getBounds().width / 2.0f - PROGRESS_BAR_WIDTH / 2.0f;
    float ballY = _ball->getPosition().y - PROGRESS_BAR_Y_OFFSET;
    ballX = std::clamp(ballX, 0.0f, static_cast<float>(_window->getSize().x) - PROGRESS_BAR_WIDTH);
    ballY = std::max(0.0f, ballY);
    _progressBar.setPosition(ballX, ballY);
    _progressBarBackground.setPosition(ballX, ballY);

    float textX = ballX + (PROGRESS_BAR_WIDTH - _powerupText.getLocalBounds().width) / 2.0f;
    float textY = ballY - TEXT_Y_OFFSET;
    textY = std::max(0.0f, textY);
    _powerupText.setPosition(textX, textY);

    std::cout << "Ball position: (" << _ball->getPosition().x << ", " << _ball->getPosition().y
        << "), Progress bar position: (" << ballX << ", " << ballY
        << "), Text position: (" << textX << ", " << textY
        << "), Show progress bar: " << (_showProgressBar ? "true" : "false") << std::endl;

    switch (powerup.first) {
    case bigPaddle:
        _powerupText.setString("big");
        _powerupText.setFillColor(paddleEffectsColour);
        _progressBar.setFillColor(paddleEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    case smallPaddle:
        _powerupText.setString("small");
        _powerupText.setFillColor(paddleEffectsColour);
        _progressBar.setFillColor(paddleEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    case slowBall:
        _powerupText.setString("slow");
        _powerupText.setFillColor(ballEffectsColour);
        _progressBar.setFillColor(ballEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    case fastBall:
        _powerupText.setString("fast");
        _powerupText.setFillColor(ballEffectsColour);
        _progressBar.setFillColor(ballEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    case fireBall:
        _powerupText.setString("fire");
        _powerupText.setFillColor(extraBallEffectsColour);
        _progressBar.setFillColor(extraBallEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    case frenzyBall:
        _powerupText.setString("frenzy");
        _powerupText.setFillColor(frenzyEffectsColour);
        _progressBar.setFillColor(frenzyEffectsColour);
        _progressBarBackground.setFillColor(sf::Color::Black);
        break;
    default:
        _powerupText.setString("");
        _progressBar.setFillColor(sf::Color::Transparent);
        _progressBarBackground.setFillColor(sf::Color::Transparent);
        _showProgressBar = false;
        break;
    }
}

void UI::lifeLost(int lives) {
    _lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render() {
    if (_showProgressBar) {
        _window->draw(_progressBarBackground);
        _window->draw(_progressBar);
    }
    _window->draw(_powerupText);
    for (sf::CircleShape life : _lives) {
        _window->draw(life);
    }
}