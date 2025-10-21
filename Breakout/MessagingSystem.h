// DEPRECATED

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class MessagingSystem
{
public:
	MessagingSystem(sf::RenderWindow* window);
	~MessagingSystem();

	void update(float dt);
	void render();
	
	void setMessage(std::string message, float timeToDisplay);

private:

	sf::RenderWindow* m_window;

	sf::Text m_message;
	sf::Font m_font;
	float m_messageTimer = 0.f;
	float m_timeToDisplay = 0.f;
};

