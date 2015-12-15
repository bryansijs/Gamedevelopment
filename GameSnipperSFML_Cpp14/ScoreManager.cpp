#include "stdafx.h"
#include "ScoreManager.h"

void ScoreManager::AddScore(int score, std::string naam)
{
	this->scores[naam] = score;
}


