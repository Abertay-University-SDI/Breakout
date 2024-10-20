#include "ButtonManager.h"

ButtonManager::ButtonManager()
{
}

ButtonManager::~ButtonManager()
{
	// Memory management after button manager is deleted, ensure all buttons assigned to it are also deleted.
	RemoveAllButtons();
}

void ButtonManager::update(float dt)
{
	if (allButtons.size() > 0)
	{
		for (int i = 0; i < allButtons.size(); i++)
		{
			allButtons[i]->update(dt);
		}
	}
}

void ButtonManager::render()
{
	if (allButtons.size() > 0)
	{
		for (int i = 0; i < allButtons.size(); i++)
		{
			allButtons[i]->render();
		}
	}
}

void ButtonManager::AddButton(Button* buttonToAdd)
{
	allButtons.push_back(buttonToAdd);
}

void ButtonManager::RemoveButton(Button* buttonToRemove)
{
	for (int i = 0; i < allButtons.size(); i++)
	{
		if (allButtons[i] == buttonToRemove)
		{
			Button* buttonPtr = allButtons[i];

			allButtons.erase(std::remove(allButtons.begin(), allButtons.end(), buttonToRemove));

			delete buttonPtr;
			buttonPtr = nullptr;
		}
	}
}

void ButtonManager::RemoveAllButtons()
{
	for (int i = 0; i < allButtons.size(); i++)
	{
		delete allButtons[i];
		allButtons[i] = nullptr;
	}

	allButtons.clear();
}
