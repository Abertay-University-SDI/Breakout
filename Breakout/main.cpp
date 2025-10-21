#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "Menu.h"
#include <iostream>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    bool gameStarted = false;
    GameManager gameManager(&window);
    Menu menu(&window);
    gameManager.playMenuMusic();
    menu.initialize();

    sf::Clock clock;
    float deltaTime;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameStarted)
            {
                menu.HandleEvent(event);
            }
        }

        if (!gameStarted)
        {
            window.setMouseCursorVisible(true);
            menu.update();

            if (menu.shouldStartGame())
            {
                gameManager.initialize();
                gameStarted = true;
            }

            window.clear();
            menu.render();
            window.display();
        }

        else
        {
            window.setMouseCursorVisible(false);
            deltaTime = clock.restart().asSeconds();

            gameManager.update(deltaTime);

            if (gameManager.returnToMenu())
            {
                menu.initialize();
                gameManager.initialize();
                gameStarted = false;
            }

            window.clear();
            gameManager.render();
            window.display();
        }
    }

    return 0;
}