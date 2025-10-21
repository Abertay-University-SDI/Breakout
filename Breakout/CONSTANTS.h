#pragma once

enum POWERUPS
{
    bigPaddle,
    smallPaddle,
    fastBall,
    slowBall,
    fireBall,
    frenzyBall,
    none
};

constexpr unsigned int WINDOW_WIDTH = 1000;
constexpr unsigned int WINDOW_HEIGHT = 800;
constexpr const char* WINDOW_TITLE = "BREAKOUT";

constexpr float PADDLE_WIDTH = 150.0f;
constexpr float PADDLE_HEIGHT = 20.0f;
constexpr float PADDLE_SPEED = 300.0f;

constexpr float BALL_RADIUS = 10.0f;
constexpr float BALL_SPEED = 5.0f;

constexpr float BRICK_WIDTH = 75.0f;
constexpr float BRICK_HEIGHT = 20.0f;
constexpr float BRICK_PADDING = 5.0f;
constexpr int BRICK_ROWS = 5;
constexpr int BRICK_COLUMNS = 10;

constexpr float POWERUP_RADIUS = 15.0f;
constexpr float POWERUP_SPEED = 150.0f;

constexpr float UI_LIFE_RADIUS = 15.0f;
constexpr float UI_LIFE_PADDING = 20.0f;

constexpr float PAUSE_TIME_BUFFER = 0.5f;
constexpr float POWERUP_FREQUENCY = 7.5f;
constexpr int INITIAL_LIVES = 3;

const sf::Color ballEffectsColour = sf::Color(100, 100, 200, 255); // blue-ish?
const sf::Color paddleEffectsColour = sf::Color(255, 250, 205); // lemon chiffon -- very fancy.
const sf::Color extraBallEffectsColour = sf::Color(41, 110, 1); // metallic green
const sf::Color frenzyEffectsColour = sf::Color(255, 0, 0); // red


