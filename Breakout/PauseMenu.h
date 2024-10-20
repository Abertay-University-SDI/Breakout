#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonManager.h"
#include "ChangeGamestateButton.h"
#include "ControlsButton.h"
#include "InputManager.h"

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow* window, InputManager* inputManager);
	~PauseMenu();

	void update(float dt);
	void render();

	bool ShouldUpdateGamestate();
	int GetRequiredGamestate();

	void ResetPauseBuffer();

private:
	sf::RenderWindow* _window;

	sf::Font _font;
	sf::Text _pauseText;

	ButtonManager* _pauseButtonManager;
	ChangeGamestateButton* exitGamestateButton;
	ControlsButton* controlsButton;

	InputManager* _inputManager;

	int requiredGamestate;
	bool bShouldUpdateGamestate;

	float timeDelayBuffer;
	float startingTimeDelayBuffer;
};
