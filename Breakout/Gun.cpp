#include "Gun.h"
#include "GameManager.h" 
#include <iostream>

Gun::Gun(sf::RenderWindow* window, GameManager* gameManager) : _window(window), _gameManager(gameManager)
{
	if(text.loadFromFile("gfx/crosshair.png"))
	{
		crosshair.setTexture(text);
	}
	else
	{
		std::cout << "ERROR LOADING TEXTURE" << std::endl;
	}

	if (buffer.loadFromFile("sfx/bang.mp3"))
	{
		sound.setBuffer(buffer);
	}
	else
	{
		std::cout << "ERROR LOADING sound" << std::endl;
	}


	font.loadFromFile("font/montS.ttf");
	cooldown_text.setFont(font);
	cooldown_text.setPosition(300, 0);
	cooldown_text.setCharacterSize(48);
	cooldown_text.setFillColor(sf::Color::Red);
}

Gun::~Gun()
{
}

void Gun::update(float dt, sf::Vector2f mouse_pos) //probably don't need to pass the mouse position and could do it all in game manager but this feels neater
{
	fire_cd += dt;
	std::string text_to_display = "Gun CD: ";
	if (fire_cd <= fire_cd_max)
	{
		int time_remaining = int(fire_cd_max - fire_cd);
		text_to_display.append(std::to_string(time_remaining) + "s");
	}
	else
	{
		text_to_display.append("Ready!");
	}

	cooldown_text.setString(text_to_display);

	current_position = mouse_pos;
	crosshair.setPosition({ current_position.x-23, current_position.y- 23 });
}




void Gun::fire()
{
	if (fire_cd >= fire_cd_max)
	{
		fire_cd = 0;

		_gameManager->getBrickManager()->checkPointCollision(current_position); //fire the gun wherever mouse is


		sound.play();
	}
}

void Gun::render()
{
	_window->draw(cooldown_text);
	_window->draw(crosshair);
}


