#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class GameManager;  // forward declaration

class Gun
{
public:
	Gun(sf::RenderWindow* window, GameManager* gameManager);
	~Gun();

	void update(float dt, sf::Vector2f mouse_pos);


	void fire();

	void render();
private:
	sf::Sprite crosshair;
	sf::Texture text;
	sf::RenderWindow* _window;
	GameManager* _gameManager;

	sf::Vector2f current_position;


	sf::SoundBuffer buffer; // Throws sf::Exception if an error occurs
	sf::Sound sound;

	sf::Font font;
	sf::Text cooldown_text;

	float fire_cd = 0, fire_cd_max = 3;
};

