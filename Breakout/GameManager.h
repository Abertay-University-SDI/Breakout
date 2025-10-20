#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"

class UI;
class MessagingSystem;
class PowerupManager;
class BrickManager;
class Ball;
class Paddle;

class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void startScreenShake(float shakelength);
    void powerupEffect(POWERUPS pu, float t);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    float getDeltaTime() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;
    sf::View* getView();


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
    sf::View _view;
    sf::Clock deltaClock;
    sf::Time dt;
    float DeltaTime;
    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;

    float _shakeTimeLimit;
    float _currentShakeTime;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn

    void screenShake();

};
