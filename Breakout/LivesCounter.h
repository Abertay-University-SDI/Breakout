#pragma once

class UI;

class LivesCounter
{
public:
	LivesCounter(int initialLives);

	void SetUI(UI* ui);

	int GetLives();
	int AddLife();
	int LoseLife();
private:
	int _lives;
	int _maxLives;

	void UpdateUI();

	UI* _ui;
};

