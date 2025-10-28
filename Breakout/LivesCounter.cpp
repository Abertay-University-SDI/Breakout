#include "LivesCounter.h"

#include "UI.h"

LivesCounter::LivesCounter(int initialLives) :_lives{initialLives},_maxLives{initialLives}, _ui{nullptr}
{
}

void LivesCounter::SetUI(UI* ui)
{
	_ui = ui;
}

int LivesCounter::GetLives()
{
	return _lives;
}

int LivesCounter::AddLife()
{
	_lives++;
	_lives = (_lives > _maxLives ? _maxLives : _lives);

	UpdateUI();

	return _lives;
}

int LivesCounter::LoseLife()
{
	--_lives;

	UpdateUI();

	return _lives;
}

void LivesCounter::UpdateUI()
{
	if (_ui)
	{
		_ui->lifeLost(_lives);
	}
}
