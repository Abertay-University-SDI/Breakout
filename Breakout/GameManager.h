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
    bool m_pause;
    float m_pauseHold;
    float m_time;
    float m_timeLastPowerupSpawned;
    int m_lives;
    bool m_levelComplete;
    std::pair<POWERUPS, float> m_powerupInEffect;

    sf::Font m_font;
    sf::Text m_masterText;

    sf::RenderWindow* m_window;
    Paddle* m_paddle;
    Ball* m_ball;
    BrickManager* m_brickManager;
    PowerupManager* m_powerupManager;
    MessagingSystem* m_messagingSystem;
    UI* m_ui;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
