#include "CameraShake.h"

//Duration in seconds, strength in max number of pixel offset
void CameraShake::startScreenShake(float dur, float str)
{
	shakeDuration = dur;
	shakeStrength = str;
}

void CameraShake::Update(float dt)
{
	if (shakeDuration > 0.f)
	{
		shakeDuration -= dt;

		//Randomises an offset, where larger is less common than smaller
		float offsetX = distributor(randomiser) * shakeStrength;
		float offsetY = distributor(randomiser) * shakeStrength;

		sf::View windView = _window->getDefaultView();
		windView.setCenter(windView.getCenter().x + offsetX, windView.getCenter().y + offsetY);
		_window->setView(windView);
	}
	else
	{
		_window->setView(_window->getDefaultView());
	}
}