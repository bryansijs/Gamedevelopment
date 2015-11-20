#pragma once
#include <string>
#include <SFML\System.hpp>
class UnitTest
{
public:
	static bool Compare(std::string identifier, int result, int expected);
	static bool Compare(std::string identifier, float result, float expected);
	static bool Compare(std::string identifier, double result, double expected);
	static bool Compare(std::string identifier, bool result, bool expected);
	static bool Compare(std::string identifier, std::string result, char expected[]);
	static bool Compare(std::string identifier, char result[], char expected[]);
	static bool Compare(std::string identifier, sf::Vector2f result, sf::Vector2f expected);
private:
	static bool PrintTrue(std::string identifier);
	static bool PrintFalse(std::string identifier);
};