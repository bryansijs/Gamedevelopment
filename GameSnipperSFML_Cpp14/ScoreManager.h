#pragma once
#include <string>
#include <map>

class ScoreManager
{
	std::map<std::string,int> scores;
	void ReadScores();
public:
	ScoreManager() { ReadScores(); };
	~ScoreManager();
	void AddScore(int score, std::string naam);
	std::map<int, std::string> GetScores();
};