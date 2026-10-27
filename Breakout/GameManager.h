#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include "Leaderboard.h"



enum class GameState
{
    Playing,
    Paused,
    LevelComplete,
    GameOver
};

class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    void startLevel();
    void restart();
    std::string bestString() const;

    GameState _state;
    int _level;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    Leaderboard _leaderboard;
    int _levelBlockCount;
    float _lastSecondsPerBlock;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text _leaderboardText;

    sf::RenderWindow* _window;
    std::unique_ptr<Paddle> _paddle;
    std::unique_ptr<Ball> _ball;
    std::unique_ptr<BrickManager> _brickManager;
    std::unique_ptr<PowerupManager> _powerupManager;
    std::unique_ptr<MessagingSystem> _messagingSystem;
    std::unique_ptr<UI> _ui;
};
