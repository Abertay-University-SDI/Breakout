#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

int main()
{
    //set inpput type
    bool controls;
    while (true) {
        std::cout << "\nAre we playing keyboard or mouse? Enter 0 for Keyboard, or 1 for Mouse:";
        std::string input_line;
        std::cin >> input_line;

        if (!input_line.empty() && input_line.at(0) == '0') {
            controls = true;
            break;
        }
        else if (!input_line.empty() && input_line.at(0) == '1') {
            controls = false;
            break;
        }
        else {
            std::cout << "\nIncorrect input, please try again!";
        }
    }


    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    GameManager gameManager(&window, controls);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;

    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);

        window.clear();
        gameManager.render();
        window.display();
    }

    return 0;
}
