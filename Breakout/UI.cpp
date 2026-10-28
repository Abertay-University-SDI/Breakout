#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

#include <iostream>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{




	const float lifeIconX = LIFE_RADIUS * 2 + LIFE_PADDING;
	const float lifeIconY = LIFE_PADDING;

	//Initialising the lives icon
	_livesIcon.setFillColor(sf::Color::Cyan);
	_livesIcon.setRadius(LIFE_RADIUS);
	_livesIcon.setPosition(lifeIconX, lifeIconY);



	if (!_font.loadFromFile("font/montS.ttf"))
	{
		//Error here! TODO look up SFMLs print line function
		std::cout << "Error! font file not loaded correctly (UI)\n";
		return;
	}

	//Initialising the lives text
	_livesText.setCharacterSize(30);
	_livesText.setPosition(lifeIconX + LIFE_RADIUS + 2 * LIFE_PADDING, lifeIconY);
	_livesText.setFont(_font);
	_livesText.setFillColor(sf::Color::White); 
	updateLivesText(lives);

	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(500, 10);
	_powerupText.setFillColor(sf::Color::Magenta);
	_powerupText.setFont(_font);


	_controlsText.setPosition(lifeIconX, 775);
	_controlsText.setFont(_font);
	_controlsText.setCharacterSize(20);
	_controlsText.setString("AD to move the paddle | P to pause | G to gamble");


	_gamblingText.setPosition(250, 700);
	_gamblingText.setFillColor(sf::Color::Magenta);
	_gamblingText.setCharacterSize(30);
	_gamblingText.setString(""); //Blank by default
	_gamblingText.setFont(_font);
}

UI::~UI()
{
}


void UI::updatePowerupText(std::string EffectText)
{


	_powerupText.setString(EffectText);

	//std::ostringstream oss;

	//switch (powerup.first)
	//{
	//case bigPaddle:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("big " + oss.str());
	//	_powerupText.setFillColor(paddleEffectsColour);
	//	break;
	//case smallPaddle:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("small " + oss.str());
	//	_powerupText.setFillColor(paddleEffectsColour);
	//	break;
	//case slowBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("slow " + oss.str());
	//	_powerupText.setFillColor(ballEffectsColour);
	//	break;
	//case fastBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("fast " + oss.str());
	//	_powerupText.setFillColor(ballEffectsColour);
	//	break;
	//case fireBall:
	//	oss << std::fixed << std::setprecision(2) << powerup.second;
	//	_powerupText.setString("fire " + oss.str());
	//	_powerupText.setFillColor(extraBallEffectsColour);
	//	break;
	//case none:
	//	_powerupText.setString("");
	//	
	//	break;
	//}
}

void UI::updateGamblingText(std::string outcomeText)
{
	_gamblingText.setString(outcomeText);
}


void UI::updateLivesText(int lives)
{
	std::string LivesCount;

	if (lives >= 0)
		LivesCount = std::to_string(lives);
	else
		LivesCount = "-";

	_livesText.setString("x" + LivesCount);
	
}

void UI::render()
{
	_window->draw(_livesText);
	_window->draw(_powerupText);
	_window->draw(_livesIcon);
	_window->draw(_controlsText);
	_window->draw(_gamblingText);
}