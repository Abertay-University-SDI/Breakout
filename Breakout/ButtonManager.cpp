#include "ButtonManager.h"

ButtonManager::ButtonManager()
{
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
			allButtons.erase(std::remove(allButtons.begin(), allButtons.end(), buttonToRemove));
		}
	}
}

void ButtonManager::RemoveAllButtons()
{
	allButtons.clear();
}