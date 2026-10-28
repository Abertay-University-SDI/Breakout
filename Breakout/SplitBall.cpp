#include "SplitBall.h"

SplitBall::SplitBall(sf::RenderWindow* window, Paddle* paddle, Ball* ball, float x_pos) : PowerupBase(window,paddle,ball,x_pos)
{
	_sprite.setFillColor(splitBallPowerupColour);
}

SplitBall::~SplitBall()
{
}

std::pair<POWERUPS, float> SplitBall::applyEffect()
{
	_ball->setAllowSplit(true, 5.f);
	
	sf::Color mainBallColour = MainBallColourInSplitBall;
	_ball->setColour(mainBallColour);

	

	return{splitBall,5.f};
}
