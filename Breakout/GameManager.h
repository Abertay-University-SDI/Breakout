#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include "Particles.h"



// The gameplay loop: serve -> play -> (lose life -> serve) -> level complete -> next level,
// or game over -> new game.
enum class GameState
{
    Serving,        // ball waits on the paddle for SPACE
    Playing,
    LevelComplete,  // SPACE starts the next level
    GameOver        // SPACE starts a new game
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
    void shake(float strength, float duration);
    void addScore(int points);

    Paddle* getPaddle() const;
    Particles* getParticles() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    void newGame();
    void startLevel(int level);
    void updateMessage();

    GameState _state;
    bool _pause;
    float _pauseHold;
    bool _spaceHeld;    // for detecting a fresh SPACE press
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    int _level;
    int _score;
    std::pair<POWERUPS, float> _powerupInEffect;

    // screen shake
    float _shakeStrength;
    float _shakeDuration;
    float _shakeTime;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;
    Particles* _particles;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
    static constexpr int BRICK_COLUMNS = 10;
    static constexpr int MAX_BRICK_ROWS = 6;            // the shader draws at most 64 boxes, paddle included
    static constexpr float LEVEL_SPEEDUP = 0.1f;        // ball gets 10% faster each level
};
