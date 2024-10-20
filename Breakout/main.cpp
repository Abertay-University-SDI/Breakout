#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "StartMenu.h"
#include <iostream>

enum Gamestate
{
    start,
    gameloop,
    pause,
    exitgame
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    GameManager gameManager(&window);
    gameManager.initialize();

    StartMenu startMenu(&window);

    Gamestate gamestate;
    gamestate = Gamestate::start;

    sf::Clock clock;
    float deltaTime;

    bool bShouldUpdateGamestate = false;
    int RequiredGamestate = 0;

    while (window.isOpen() && gamestate != Gamestate::exitgame)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        // Update current gamestate
        switch(gamestate)
        {
        case Gamestate::start:

            startMenu.update(deltaTime);
            if (startMenu.ShouldUpdateGamestate())
            {
                bShouldUpdateGamestate = true;
                RequiredGamestate = startMenu.GetRequiredGamestate();
            }

            break;
        case Gamestate::gameloop:

            gameManager.update(deltaTime);

            break;
        case Gamestate::pause:
            break;
        }

        // Render appropriate window
        window.clear();
        switch(gamestate)
        {
        case Gamestate::start:
            startMenu.render();
            break;

        case Gamestate::gameloop:
            gameManager.render();
            break;

        case Gamestate::pause:

            break;
        }
        window.display();

        // Swap gamestate after rendering and updating this frame
        if (bShouldUpdateGamestate)
        {
            switch (RequiredGamestate)
            {
            case 0:
                gamestate = Gamestate::start;
                break;
            case 1:
                gamestate = Gamestate::gameloop;
                break;
            case 2:
                gamestate = Gamestate::pause;
                break;
            case 3:
                gamestate = Gamestate::exitgame;
                break;
            }
        }
    }

    return 0;
}
