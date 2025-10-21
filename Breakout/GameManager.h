#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include <iostream>

class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void enterFrenzy();
    void render();
    void levelComplete();
    void startBossLevel();
    void triggerShake(float duration, float magnitude); 
    bool isBossLevel() const;
    bool returnToMenu() const;
    void playWallHitSound();
    void playPaddleHitSound(); 
    void playBrickHitSound(); 
    void playMenuMusic();
    void playGameMusic();
    void playBossMusic();
    void playerHitSound();
    void stopMusic();

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
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;

    float _shakeDuration;
    float _shakeMagnitude;
    sf::Vector2f _shakeOffset;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    bool _levelStarted;
    float _levelStartTimer;

    bool _isGameOver;
    float _gameOverTimer;

    bool _isBossLevel;
    float _bossLevelStartTimer;

    float _lifeLostTimer;

    sf::SoundBuffer _wallHitBuffer; 
    sf::SoundBuffer _paddleHitBuffer; 
    sf::SoundBuffer _brickHitBuffer; 
    sf::SoundBuffer _playerHitBuffer; 
    sf::Sound _wallHitSound; 
    sf::Sound _paddleHitSound; 
    sf::Sound _brickHitSound;
    sf::Sound _playerHitSound; 

    sf::Music _menuMusic;
    sf::Music _gameMusic;
    sf::Music _bossMusic;

    float windowWidth = static_cast<float>(WINDOW_WIDTH);
    float windowHeight = static_cast<float>(WINDOW_HEIGHT);

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;
    static constexpr float SHAKE_DURATION = 0.3f;
    static constexpr float SHAKE_MAGNITUDE = 5.0f;
    static constexpr float FRENZY_DURATION = 5.0f;
    static constexpr float FRENZY_MAGNITUDE = 5.0f;
    static constexpr float GAME_OVER_DISPLAY_TIME = 2.0f;
    static constexpr float BOSS_LEVEL_START_DELAY = 2.0f;
    static constexpr float LIFE_LOST_DISPLAY_TIME = 0.5f; 
    static constexpr int RAND_POWERUP_TIME = 400;
};