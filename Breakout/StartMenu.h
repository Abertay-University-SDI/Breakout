#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonManager.h"
#include "ChangeGamestateButton.h"

class StartMenu
{
public:
	StartMenu(sf::RenderWindow* window);
	~StartMenu();

	void update(float dt);
	void render();

	bool ShouldUpdateGamestate();
	int GetRequiredGamestate();

private:
	sf::RenderWindow* _window;

	sf::Font _font;
	sf::Text _startText;

	ButtonManager* _startButtonManager;
	ChangeGamestateButton* startGamestateButton;
	ChangeGamestateButton* exitGamestateButton;

	int requiredGamestate;
	bool bShouldUpdateGamestate;
};
