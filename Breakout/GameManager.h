#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
//#include "Ball.h"
#include "BrickManager.h"
//#include "PowerupManager.h"
#include "MessagingSystem.h"
#include <algorithm>
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window, bool cont);
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

    void createSecondaryBall();
    void deleteSecondaryBall(Ball* ball);

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
    std::vector<Ball*> _secondaryBalls;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;


    bool controls;

    int powerUpChance = 700;

    bool shake = false;
    int randShake = 0;
    int shakeIntensity = 50;
    float shakeTime = 0;
    float shakeEndTime = 0.2;
    float shakeIntervals = 0.03;
    float lastShake = 0;
};
