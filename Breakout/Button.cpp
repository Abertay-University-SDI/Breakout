#include "Button.h"
#include <iostream>

Button::Button(sf::RenderWindow* window) : 
_window(window){
	_keyPressed = false;
	_clicked = false;
	_active = false;
}

void Button::handleInput() {
	if (_active && sf::Mouse::isButtonPressed(sf::Mouse::Left) && (sf::Mouse::getPosition(*_window).x >= this->getPosition().x && sf::Mouse::getPosition(*_window).x <= this->getPosition().x + this->getSize().x && sf::Mouse::getPosition(*_window).y >= this->getPosition().y && sf::Mouse::getPosition(*_window).y <= this->getPosition().y + this->getSize().y)) {
		_keyPressed = true;
		return;
	}
	else {
		_keyPressed = false;
		_clicked = false;
	}
}

bool Button::isClicked() {
	if (_keyPressed) {
		if (_clicked) {
			return false;
		}
		else {
			_clicked = true;
			return _clicked;
		}
	}
	else {
		_clicked = false;
		return _clicked;
	}
}

void Button::render() {
	if (_active) {
		_window->draw(*this);
		_window->draw(_text);
	}
}

void Button::setActive(bool active) {
	_active = active;
}

bool Button::getActive() { return _active; };
sf::Text* Button::getText() { return &_text; };
