#include "Trail.h"
#include "GameManager.h"

Trail::Trail(sf::RenderWindow* window, GameManager* gameManager)
	: _window(window), _gameManager(gameManager)
{
	//trailTexture.loadFromFile("images/trail.png");
}

Trail::~Trail()
{
}

// @brief This creates a trail effect behind the ball.
// @param ballPosition | The middle position of the ball.
void Trail::CreateTrail(sf::Vector2f ballPosition)
{
	trailVector.push_back(sf::RectangleShape(sf::Vector2f(SIZE_OF_TRAIL, SIZE_OF_TRAIL)));
	trailVector.back().setPosition(ballPosition- sf::Vector2f(SIZE_OF_TRAIL/2, SIZE_OF_TRAIL/2));
	trailVector.back().setFillColor(sf::Color(255, 255, 255, 255));
}

// @param dt | DeltaTime
void Trail::render(float dt)
{
	for (auto aTrail = trailVector.begin(); aTrail != trailVector.end();) // for every trail sprite
	{
		_window->draw(*aTrail); // draw the trail

		sf::Uint8 alpha = aTrail->getFillColor().a-1*dt; // get the the new alpha

		if (alpha < 1)
			aTrail = trailVector.erase(aTrail);
		else
		{
			aTrail->setFillColor(sf::Color(255, 255, 255, (alpha))); // fading out, remove 5 from the alpha value
			++aTrail;
		}

		
	}
}