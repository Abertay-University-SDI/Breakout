#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "GamblingSystem.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "EffectableSystem.h"
#include "UI.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void addLives(int lives);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    /*(safer) update of the UI object with the gambling systems outcome text*/
    void updateGamblingUI(std::string str);


    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    inline EffectableSystem* getEffectableSystem() const { return _effectableSystem; };
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;

    sf::Font _font;
    sf::Text _masterText;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    /*Handles the game's effect side of the powerups*/
    EffectableSystem* _effectableSystem;
    /*Handles the physical powerup objects in the game world*/
    PowerupManager* _powerupManager;

    MessagingSystem* _messagingSystem;
    GamblingSystem* _gamblingSystem;
    UI* _ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn


public:


    /*GETTERS AND SETTERS*/

    inline int getLives() { return _lives; }
};
