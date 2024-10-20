#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow* window, InputManager* inputManager) : _window(window), _inputManager(inputManager), bShouldUpdateGamestate(false), requiredGamestate(2), timeDelayBuffer(0.3f), startingTimeDelayBuffer(0.3f)
{
    _font.loadFromFile("font/montS.ttf");

    _pauseText.setFont(_font);
    _pauseText.setPosition(400, 300);
    _pauseText.setCharacterSize(48);
    _pauseText.setFillColor(sf::Color::Yellow);
    _pauseText.setString("Pause");

    exitGamestateButton = new ChangeGamestateButton(_window, sf::Vector2f(600, 500), sf::Vector2f(200, 75), _font, 3, 28, "Exit", sf::Color::Black, sf::Color::Red);
    controlsButton = new ControlsButton(_window, sf::Vector2f(200, 500), sf::Vector2f(200, 75), _font, _inputManager, 24, 12, "Change Controls", sf::Color::Black, sf::Color::Green);

    _pauseButtonManager = new ButtonManager();
    _pauseButtonManager->AddButton(exitGamestateButton);
    _pauseButtonManager->AddButton(controlsButton);
}

PauseMenu::~PauseMenu()
{
    delete _pauseButtonManager;
    _pauseButtonManager = nullptr;
}

void PauseMenu::update(float dt)
{
    _pauseButtonManager->update(dt);

    if (timeDelayBuffer > 0)
    {
        timeDelayBuffer -= dt;
    }

    if (timeDelayBuffer <= 0)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            bShouldUpdateGamestate = true;
            requiredGamestate = 1;
        }
    } 

    if (exitGamestateButton->ShouldChangeGamestate())
    {
        bShouldUpdateGamestate = true;
        requiredGamestate = exitGamestateButton->GetRequiredGamestate();
    }
}

void PauseMenu::render()
{
    _window->draw(_pauseText);

    _pauseButtonManager->render();
}

bool PauseMenu::ShouldUpdateGamestate()
{
    return bShouldUpdateGamestate;
}

int PauseMenu::GetRequiredGamestate()
{
    return requiredGamestate;
}

void PauseMenu::ResetPauseBuffer()
{
    timeDelayBuffer = startingTimeDelayBuffer;
    bShouldUpdateGamestate = false;
}
