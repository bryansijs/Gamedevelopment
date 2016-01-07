#include "stdafx.h"
#include "ScoreManager.h"
#include <iostream>
#include <fstream>

void ScoreManager::ReadScores()
{
	scores.clear();
	std::ifstream highScorefile;
	highScorefile.open("./Resources/save/highscore.txt");
	if (highScorefile.is_open())
	{
		std::string key;
		int value;
		while(highScorefile >> key >> value)
		{
			scores[key] = value;
		}
	}
}

void ScoreManager::AddScore(int score, std::string naam)
{
	if(this->scores.find(naam) == this->scores.end())
	{
		this->scores[naam] = score;
	}
	else
	{
		this->scores[naam] = this->scores[naam] + score;
	}
}

std::map<std::string,int> ScoreManager::GetScores()
{
	return this->scores;
}

void ScoreManager::Save()
{
	std::ofstream highScorefile ("./Resources/save/highscore.txt");
	if (highScorefile.is_open())
	{
		highScorefile.clear();
		if (this->scores.size() > 0)
		{
			for(auto const &score : scores)
			{
				highScorefile << score.first << " " << score.second;
			}
			highScorefile.close();
		}
	}
	else
		std::cerr << "could not open highScore file";
}

