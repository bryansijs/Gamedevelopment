#pragma once
#include <string>

class UnitTest
{
public:
	static bool Compare(std::string identifier, int result, int expected);
	static bool Compare(std::string identifier, float result, float expected);
	static bool Compare(std::string identifier, double result, double expected);
	static bool Compare(std::string identifier, bool result, bool expected);
	static bool Compare(std::string identifier, std::string result, char expected[]);
	static bool Compare(std::string identifier, char result[], char expected[]);
private:
	static bool PrintTrue(std::string identifier);
	static bool PrintFalse(std::string identifier);
};