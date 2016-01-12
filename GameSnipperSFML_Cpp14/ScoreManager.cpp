#include "stdafx.h"
#include "ScoreManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

template<typename A, typename B>
std::pair<B, A> flip_pair(const std::pair<A, B> &p)
{
	return std::pair<B, A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B, A> flip_map(const std::map<A, B> &src)
{
	std::multimap<B, A> dst;
	std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
		flip_pair<A, B>);
	return dst;
}

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
	dst = flip_map(scores);

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

std::multimap<int, std::string> ScoreManager::GetScores()
{
	return this->dst;
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

