#include "FailScreen.h"
#include <ctime>

FailScreen::FailScreen(sf::RenderWindow* window, GameManager* gameManager)
{
	_window = window;
	_gameManager = gameManager;

	isAlive = false;
	_time = 0;

	_texture.loadFromFile("gfx/dustbaby.png");

	_sprite.setTexture(_texture);

	_sprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	_sprite.setScale(sf::Vector2f(3.2, 2.5));

}

FailScreen::~FailScreen()
{

}

void FailScreen::update(float dt)
{
	if (isAlive)
	{
		_time = _time + dt;
		if (_time > 0.2)
		{
			isAlive = false;
			_time = 0;
		}
	}
}

void FailScreen::reset()
{
	isAlive = false;
	_time = 0;
}

void FailScreen::lifeLost(int lives)
{
	isAlive = true;

}

void FailScreen::render()
{
	if (isAlive)
	{
		_window->draw(_sprite);
	}
}

