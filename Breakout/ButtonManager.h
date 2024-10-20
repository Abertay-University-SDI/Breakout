#pragma once

#include <vector>
#include "Button.h"
#include "InputManager.h"

class ButtonManager
{
public:
	ButtonManager();

	void update(float dt);
	void render();

	void AddButton(Button* buttonToAdd);
	void RemoveButton(Button* buttonToRemove);
	void RemoveAllButtons();

private:
	InputManager* _inputManager;

	std::vector<Button*> allButtons;
};