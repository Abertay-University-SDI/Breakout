#pragma once
#include <SFML/Graphics.hpp>

// implemented powerups
enum POWERUPS
{
    bigPaddle,
    smallPaddle,
    fastBall,
    slowBall,
    fireBall,
    none
};

// Window settings
constexpr unsigned int WINDOW_WIDTH = 1000;
constexpr unsigned int WINDOW_HEIGHT = 800;
constexpr const char* WINDOW_TITLE = "Breakout";

// Assets
constexpr const char* FONT_PATH = "font/montS.ttf";

// Paddle settings
constexpr float PADDLE_WIDTH = 150.0f;
constexpr float PADDLE_HEIGHT = 20.0f;
constexpr float PADDLE_SPEED = 300.0f;

// Ball settings
constexpr float BALL_RADIUS = 10.0f;
constexpr float BALL_SPEED = 400.0f;

// Brick settings
constexpr float BRICK_WIDTH = 80.0f;
constexpr float BRICK_HEIGHT = 30.0f;
constexpr float BRICK_PADDING = 5.0f;
constexpr float BRICK_TOP_PADDING = 100.0f;
constexpr int BRICK_ROWS = 5;
constexpr int BRICK_COLUMNS = 10;

// Power-up settings
constexpr float POWERUP_RADIUS = 20.0f;
constexpr float POWERUP_SPEED = 250.0f;             // speed of fall
constexpr float POWERUP_SWAY_AMPLITUDE = 80.0f;     // waviness of fall

// UI settings
constexpr float UI_LIFE_RADIUS = 15.0f;
constexpr float UI_LIFE_PADDING = 20.0f;

// Other game settings
constexpr float PAUSE_TIME_BUFFER = 0.5f;
constexpr float POWERUP_FREQUENCY = 7.5f;
constexpr int POWERUP_SPAWN_ODDS = 700;
constexpr int INITIAL_LIVES = 3;

// Colour Palette
inline const sf::Color ballEffectsColour = sf::Color(100, 100, 200, 255); // blue-ish?
inline const sf::Color paddleEffectsColour = sf::Color(255, 250, 205); // lemon chiffon -- very fancy.
inline const sf::Color extraBallEffectsColour = sf::Color(41, 110, 1); // metallic green


