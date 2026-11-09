#include "UI.h"
#include "GameManager.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace
{
	// Constants for the powerup bar
	const float powerupBarX = 800.0f;
	const float powerupBarY = 50.0f;
	const float powerupBarWidth = 185.0f;
	const float powerupBarHeight = 20.0f;

	// Center Pause menu text and labels
	void centerText(sf::Text& text, float x, float y) {

		const sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		text.setPosition(x, y);
	}

}
UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}

	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(800, 10);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);

	///INITIALIZE POWERUP BAR

	//Powerup bar background
	_powerupBarBackground.setSize({powerupBarWidth, powerupBarHeight});
	_powerupBarBackground.setPosition(powerupBarX, powerupBarY);
	_powerupBarBackground.setFillColor(sf::Color(50, 50, 50, 200));

	//Powerup bar
	_powerupBar.setSize({ 0.f, powerupBarHeight });
	_powerupBar.setPosition(powerupBarX, powerupBarY);

	///INITIALIZE MENU
	const sf::Vector2f win(_window->getSize());

	// Pause menu background
	_pauseScreen.setSize(win);
	_pauseScreen.setFillColor(sf::Color(0, 0, 0, 150));

	// Pause menu options
	_pauseMenu.setFillColor(sf::Color(25, 25, 25, 200));
	_pauseMenu.setOutlineColor(sf::Color::Cyan);
	_pauseMenu.setOutlineThickness(4.f);

	_pauseText.setFont(_font);
	_pauseText.setCharacterSize(48);
	_pauseText.setFillColor(sf::Color::Cyan);

	//Menu Options
	showMenu("Paused", { 
		{"Resume", PauseOptions::RESUME}, 
		{"Restart", PauseOptions::RESTART}, 
		{"Exit", PauseOptions::EXIT} 
	});
}

UI::~UI()
{
}

void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	// Update the powerup text
	switch (powerup.first)
	{
	case bigPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case smallPaddle:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small " + oss.str());
		_powerupText.setFillColor(paddleEffectsColour);
		break;
	case slowBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fastBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast " + oss.str());
		_powerupText.setFillColor(ballEffectsColour);
		break;
	case fireBall:
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire " + oss.str());
		_powerupText.setFillColor(extraBallEffectsColour);
		break;
	case none:
		_powerupText.setString("");
		break;
	}

	// Update the powerup bar
	// If there is no powerup, reset the bar
	if (powerup.first == none)
	{
		_powerupBarMaxTime = 0.f;
		_powerupBar.setSize({ 0.f, powerupBarHeight });
	}
	else
	{
		// If the powerup has changed, update the bar
		if (powerup.first != _lastPowerup || powerup.second > _powerupBarMaxTime)
			_powerupBarMaxTime = powerup.second;		
		
		//Recalculate the fraction of the bar to fill based on the remaining time and the max time
		const float fraction = (_powerupBarMaxTime > 0.f)
			? std::clamp(powerup.second / _powerupBarMaxTime, 0.f, 1.f) : 0.f;

		_powerupBar.setSize({ powerupBarWidth * fraction, powerupBarHeight });
		_powerupBar.setFillColor(_powerupText.getFillColor());
	}

	// Set last powerup to current powerup
	_lastPowerup = powerup.first;
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::render()
{
	_window->draw(_powerupText);

	// Draw powerup bar if there is a powerup in effect
	if (!_powerupText.getString().isEmpty())
	{
		_window->draw(_powerupBarBackground);
		_window->draw(_powerupBar);
	}

	// Draw lives
	for (const sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}

// Get the index of the pause option at the given position
int UI::getPauseAt(sf::Vector2f pos) const
{
	for (int i = 0; i < static_cast<int>(_pauseOptions.size()); ++i)
	{
		if (_pauseOptions[i].getGlobalBounds().contains(pos))
		{
			return i;
		}
	}

	return -1;
}

// Update the currently selected pause option based on user input
void UI::updatePauseOption(int delta)
{
	const int count = static_cast<int>(_pauseOptions.size());
	if (count == 0)
		return;

	_selectedOption = (_selectedOption + delta % count + count) % count;
}

// Reset the pause menu to its initial state
void UI::resetPauseMenu()
{
	_selectedOption = 0;
}

// Render the pause menu
void UI::renderPauseMenu()
{
	// Draw the pause screen and menu
	_window->draw(_pauseScreen);
	_window->draw(_pauseMenu);
	_window->draw(_pauseText);

	for (int i = 0; i < static_cast<int>(_pauseOptions.size()); ++i)
	{
		const bool isSelected = (i == _selectedOption);
		
		// Set the fill color based on whether the option is selected
		_pauseOptions[i].setFillColor(isSelected ? sf::Color(100, 100, 100) : sf::Color(50, 50, 50));
		_pauseOptions[i].setOutlineColor(isSelected ? sf::Color::Cyan : sf::Color::White);
		_pauseLabels[i].setFillColor(isSelected ? sf::Color::Cyan : sf::Color::White);

		_window->draw(_pauseOptions[i]);
		_window->draw(_pauseLabels[i]);
	}
}

// Set the currently selected pause option
void UI::setPauseOption(int option)
{
	if (option >= 0 && option < static_cast<int>(_pauseOptions.size()))
	{
		_selectedOption = option;
	}	
}

// Return the currently selected pause option
PauseOptions UI::getPauseOption() const
{
	return _menuOptions.empty() ? PauseOptions::RESUME : _menuOptions[_selectedOption];
}

// Show menu based on the provided title and entries
void UI::showMenu(const std::string& title, const std::vector<std::pair<std::string, PauseOptions>>& entries)
{
	// Initialize variables for the menu
	const sf::Vector2f win(_window->getSize());
	const int count = static_cast<int>(entries.size());
	const sf::Vector2f menuSize(360.f, 100.f + 60.f * count);
	const float menuTop = (win.y - menuSize.y) / 2.f;

	// Set up the pause menu background
	_pauseMenu.setSize(menuSize);
	_pauseMenu.setOrigin(menuSize / 2.f);
	_pauseMenu.setPosition(win / 2.f);

	_pauseText.setString(title);
	centerText(_pauseText, win.x / 2.f, menuTop + 50.f);

	_pauseOptions.clear();
	_pauseLabels.clear();
	_menuOptions.clear();	

	// Create new menu options and labels based on the provided entries
	const sf::Vector2 optionSize(300.f, 50.f);
	
	for (int i = 0; i < count; ++i)
	{
		sf::RectangleShape button;
		button.setSize(optionSize);
		button.setOrigin(optionSize / 2.f);
		button.setPosition(win.x / 2.f, menuTop + 110.f + i * 60.f);
		button.setOutlineThickness(2.f);
		_pauseOptions.push_back(button);

		sf::Text label;
		label.setFont(_font);
		label.setString(entries[i].first);
		label.setCharacterSize(30);
		centerText(label, button.getPosition().x, button.getPosition().y);
		_pauseLabels.push_back(label);
		_menuOptions.push_back(entries[i].second);
	}

	_selectedOption = 0;
}
