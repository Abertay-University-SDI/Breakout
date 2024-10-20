#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "StartMenu.h"
#include "PauseMenu.h"
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

    PauseMenu pauseMenu(&window, gameManager.getInputManager());

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
            if (gameManager.ShouldUpdateGamestate())
            {
                bShouldUpdateGamestate = true;
                RequiredGamestate = gameManager.GetRequiredGamestate();
            }

            break;
        case Gamestate::pause:

            pauseMenu.update(deltaTime);
            if (pauseMenu.ShouldUpdateGamestate())
            {
                bShouldUpdateGamestate = true;
                RequiredGamestate = pauseMenu.GetRequiredGamestate();
            }

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
            pauseMenu.render();
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
                if (gamestate == Gamestate::pause)
                {
                    gameManager.resetPauseBuffer();
                }
                gamestate = Gamestate::gameloop;
                break;
            case 2:
                if (gamestate == Gamestate::gameloop)
                {
                    pauseMenu.ResetPauseBuffer();
                }
                gamestate = Gamestate::pause;
                break;
            case 3:
                gamestate = Gamestate::exitgame;
                break;
            }

            bShouldUpdateGamestate = false;
        }
    }

    return 0;
}
