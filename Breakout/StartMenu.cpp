#include "StartMenu.h"

StartMenu::StartMenu(sf::RenderWindow* window) : _window(window), bShouldUpdateGamestate(false), requiredGamestate(0)
{
    _font.loadFromFile("font/montS.ttf");
    _startText.setFont(_font);
    _startText.setPosition(400, 300);
    _startText.setCharacterSize(48);
    _startText.setFillColor(sf::Color::Yellow);
    _startText.setString("Breakout");

    startGamestateButton = new ChangeGamestateButton(_window, sf::Vector2f(200, 500), sf::Vector2f(200, 75), _font, 1, 28, "Start", sf::Color::Black, sf::Color::Green);
    exitGamestateButton = new ChangeGamestateButton(_window, sf::Vector2f(600, 500), sf::Vector2f(200, 75), _font, 3, 28, "Exit", sf::Color::Black, sf::Color::Red);

    _startButtonManager = new ButtonManager;
    
    _startButtonManager->AddButton(startGamestateButton);
    _startButtonManager->AddButton(exitGamestateButton);
}

StartMenu::~StartMenu()
{
    delete _startButtonManager;
    _startButtonManager = nullptr;
}

void StartMenu::update(float dt)
{
    _startButtonManager->update(dt);

    if (startGamestateButton->ShouldChangeGamestate())
    {
        bShouldUpdateGamestate = true;
        requiredGamestate = startGamestateButton->GetRequiredGamestate();
    }
    else if (exitGamestateButton->ShouldChangeGamestate())
    {
        bShouldUpdateGamestate = true;
        requiredGamestate = exitGamestateButton->GetRequiredGamestate();
    }
}

void StartMenu::render()
{
    _window->draw(_startText);

    _startButtonManager->render();
}

bool StartMenu::ShouldUpdateGamestate()
{
    return bShouldUpdateGamestate;
}

int StartMenu::GetRequiredGamestate()
{
    return requiredGamestate;
}
