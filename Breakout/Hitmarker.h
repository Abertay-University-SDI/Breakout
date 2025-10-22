#pragma once
#include <SFML/Graphics.hpp>

class Hitmarker {
public:

    Hitmarker(sf::RenderWindow* window, sf::Vector2f spawnPosition, sf::Font *font);
    ~Hitmarker();
    void update(float dt);
    void render(sf::RenderWindow& window);

private:

    sf::Font _font;
    sf::Text _text;
    sf::RenderWindow* _window;
};
