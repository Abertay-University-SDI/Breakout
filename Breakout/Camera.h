#pragma once
#include <SFML/Graphics.hpp>


class GameManager;  // forward declaration



class Camera {
public:
    Camera(sf::RenderWindow* window, GameManager* gameManager);
    ~Camera();
    void update(float dt);
    void render();
    void shake();

    //temp
    float getShakeVal();

    float _shakeVal;
    sf::Vector2f _offset;
    float _offsetRot;
private:

    sf::RenderWindow* _window;
    sf::View _view;
    sf::Vector2f _centre;
    
    GameManager* _gameManager;  // Reference to the GameManager
};

