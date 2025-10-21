#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"

class GameManager {
public:
    GameManager();
    void initialize();
    void update(float dt);
    void loseLife();
    void render(sf::RenderWindow& window);
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);
    void addScreenShake(float amount);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    UI* getUI() const;

private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _nextPowerUpTime;
    float _screenShakePower;
    int _lives;
    bool _levelComplete;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;

    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;
};
