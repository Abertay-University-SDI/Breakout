#include "MessagingSystem.h"

MessagingSystem::MessagingSystem(sf::RenderWindow* window)
{
	m_window = window;
	m_message.setCharacterSize(24);
	m_font.loadFromFile("font/montS.ttf");
	m_message.setFont(m_font);
	m_message.setFillColor(sf::Color::White);
	m_message.setPosition(10, 10);
		
}

MessagingSystem::~MessagingSystem()
{
}

void MessagingSystem::update(float dt)
{
	// early exit
	if (m_timeToDisplay == 0.f) return;
	
	// increment timer if it should be running, or reset message if expired.
	if (m_messageTimer < m_timeToDisplay)
	{
		m_messageTimer += dt;
	}
	else
	{
		m_message.setString("");
		m_timeToDisplay = 0.f;
		m_messageTimer = 0.f;
	}
}

void MessagingSystem::render()
{
	m_window->draw(m_message);
}

// update alert with str <message> for float <timeToDisplay> in seconds.
void MessagingSystem::setMessage(std::string message, float timeToDisplay)
{
	m_message.setString(message);
	m_timeToDisplay = timeToDisplay;
}
