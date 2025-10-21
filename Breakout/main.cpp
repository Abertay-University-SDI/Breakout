#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include "CONSTANTS.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y), "Breakout", sf::Style::Default, settings);
    GameManager gameManager{};
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
        gameManager.render(window);
        window.display();
    }

    return 0;
}
