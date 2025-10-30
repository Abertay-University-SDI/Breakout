#include "ScreenShake.h"

void ScreenShake::update() {

	if (shakeDuration > 0) {
		//sets the offset for the screen shake for the correct duration
		shakeDuration -= 0.01f;
		float offsetY = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.f * shakeMagnitude;
		float offsetX = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 2.f * shakeMagnitude;
		shakeOffset = sf::Vector2f(offsetX, offsetY);
	}
	else {
		//returns the screen offset to normal
		shakeOffset = sf::Vector2f(0, 0);
	}
}

void ScreenShake::render(sf::RenderWindow& _window) {
	sf::View shakenView = _window.getDefaultView();
	shakenView.move(shakeOffset);
	_window.setView(shakenView);

}

void ScreenShake::startShake() {
	shakeDuration = 0.2f;
}