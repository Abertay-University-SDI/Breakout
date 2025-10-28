#include "PowerupContainer.h"

#include "CONSTANTS.h"

#include "Paddle.h"

PowerupContainer::PowerupContainer(sf::RenderWindow* window, sf::Color color, float duration)
	:_window{ window }, _color{ color }, _velocity{ 0,250.f },
	_shouldBeDestroyed{false},_duration{duration}
{
	_sprite.setRadius(POWERUP_RADIUS);
	_sprite.setFillColor(color);
}

PowerupContainer::PowerupContainer(PowerupContainer& first) 
	:_window{ first._window },_color{first._color},_velocity{first._velocity}
	, _sprite{ first._sprite }, _shouldBeDestroyed{ false },_duration{first._duration}
{
	//Copy effects (uses custom function that circumvents copy constructor limitations)
	for (std::shared_ptr<BaseEffect>& effect : first._effects)
	{
		_effects.emplace_back(effect->CopyEffect());
	}
}

void PowerupContainer::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void PowerupContainer::AddEffect(BaseEffect* effect)
{
	_effects.emplace_back(effect);
}

void PowerupContainer::Update(float dt)
{
	_sprite.move(_velocity * dt);
	
	//Flag powerup for destruction once object should be destroyed
	if (_sprite.getPosition().y + _sprite.getRadius() * 2 >= _window->getSize().y)
	{
		_shouldBeDestroyed = true;
		//TODO: Clear effects
	}
}

void PowerupContainer::Render()
{
	_window->draw(_sprite);
}

void PowerupContainer::ApplyEffect()
{
	for (std::shared_ptr<BaseEffect>& effect : _effects)
	{
		effect->ApplyEffect(_duration);
	}
}

bool PowerupContainer::CheckCollisionWithPaddle(Paddle* paddle)
{
	if (_sprite.getGlobalBounds().intersects(paddle->getBounds()))
	{
		_shouldBeDestroyed = true;
		ApplyEffect();
		return true;
	}
	return false;
}

const std::vector<std::shared_ptr<BaseEffect>>& PowerupContainer::getEffects()
{
	return _effects;
}
