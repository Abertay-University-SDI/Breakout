#pragma once

class ScoreManager
{
public:
	ScoreManager(int score);
	void incrementScore(int score);
	int getScore();
private:
	int _score;
};

