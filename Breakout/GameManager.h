#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"

#include "AudioManager.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window, AudioManager* audioManager);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    void shakeCamera(float duration, int x, int y, float fade);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;

    AudioManager* audio;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    int spawnChance = 700;

    bool shaking = false;
    float shakeDuration = 0.0f;
    float shakeFade = 0.5f;
    int shakeX = 0;
    int shakeY = 0;
    float originalViewX = 0.0f;
    float originalViewY = 0.0f;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
