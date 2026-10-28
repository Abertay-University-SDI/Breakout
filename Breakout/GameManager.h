#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "CameraManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"

class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void render();
    void loseLife();
    void gainLife();
    void gameOver();
    void levelComplete();
    void scoreCount();
    void multiBall(bool value);
    void powerupEffect(POWERUPS pu, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    int _bricksRemaining;
    int _highScore;
    bool _gameOver;
    bool _levelComplete;
    bool _lifeLost;
    bool _isMultiBall;
    std::pair<POWERUPS, float> _powerupInEffect;
    std::string _bricksTotal;
    std::string _scoreDisplay;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    CameraManager* _cameraManager;
    Paddle* _paddle;
    Ball* _ball;
    Ball* _extraBalls[3];
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
