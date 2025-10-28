#pragma once

#include <string>

//Not really an interface anymore
class BaseEffect
{
public:
	virtual void ApplyEffect(float duration) { _durationLeft = duration; }
	virtual void EndEffect() = 0;

	virtual void UpdateEffect(float dt);

	virtual BaseEffect* CopyEffect() = 0; 

	virtual std::string GetName() { return "Default effect name"; }

	bool ShouldBeDestroyed() { return _shouldBeDestroyed; }
	float getDurationLeft() { return _durationLeft; }

private:
	float _durationLeft;
	bool _shouldBeDestroyed;
};