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
	void Reload() { ReadScores(); };
	void AddScore(int score, std::string naam);
	std::map<std::string,int> GetScores();
	void Save();
};