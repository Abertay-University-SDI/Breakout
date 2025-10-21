// DEPRECATED

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
class MessagingSystem
{
public:
	MessagingSystem();
	~MessagingSystem();

	void update(float dt);
	void render(sf::RenderWindow& window);
	
	void setMessage(std::string message, float timeToDisplay);

private:
	sf::Text _message;
	sf::Font _font;
	float _messageTimer = 0.f;
	float _timeToDisplay = 0.f;
};

