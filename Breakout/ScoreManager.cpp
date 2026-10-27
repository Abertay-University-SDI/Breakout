#include "ScoreManager.h"

ScoreManager::ScoreManager(int score) : _score(score) {
	_score = 0;
}

void ScoreManager::incrementScore(int score) {
	_score += score;
}

int ScoreManager::getScore() {
	return _score;
}