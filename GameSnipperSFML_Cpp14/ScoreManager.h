#pragma once
#include <string>
#include <map>

class ScoreManager
{
	std::map<std::string,int> scores;
	std::multimap<int, std::string> dst;
	void ReadScores();
public:
	ScoreManager() { ReadScores(); };
	~ScoreManager();
	void Reload() { ReadScores(); };
	void AddScore(int score, std::string naam);
	std::multimap<int, std::string> GetScores();
	void Save();
};