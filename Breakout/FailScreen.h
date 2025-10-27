#pragma once
#include <SFML/Graphics.hpp>

class GameManager;

class FailScreen
{ 
public:
    FailScreen(sf::RenderWindow* window, GameManager* gameManager);
    ~FailScreen();
    void update(float dt);
    void render();
    void reset();
    void lifeLost(int lives);


private:
    sf::RenderWindow* _window;
    sf::Sprite _sprite;
    bool isAlive;
    sf::Texture _texture;
    float _time;

    GameManager* _gameManager;  // Reference to the GameManager

};

