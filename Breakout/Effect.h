#pragma once

class GameManager;

class Effect
{
public:
	Effect(GameManager* gameManager, float duration);

	virtual void update(float dt);

	virtual void applyEffect() = 0;
	virtual void endEffect() = 0;

	void setDuration(float duration);

	float getDuration() const;
	
protected:

	GameManager* _gameManager;
	float _duration;
};

