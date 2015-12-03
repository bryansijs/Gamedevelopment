#include "stdafx.h"
#include "UnitTest.h"
#include "ConsoleColor.h"
#include <iostream>

bool UnitTest::Compare(std::string identifier, int result, int expected)
{
	if (result == expected)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::Compare(std::string identifier, b2Vec2 result, b2Vec2 expected)
{
	if (result.x == expected.x && result.y == expected.y)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}


bool UnitTest::Compare(std::string identifier, float result, float expected)
{
	if (result == expected)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::Compare(std::string identifier, double result, double expected)
{
	if (result == expected)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::Compare(std::string identifier, bool result, bool expected)
{
	if (result == expected)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::Compare(std::string identifier, std::string result, char expected[])
{
	if (strcmp(result.c_str(), expected) == 0)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::Compare(std::string identifier, char result[], char expected[])
{
	if (strcmp(result, expected) == 0)
		return PrintTrue(identifier);
	return PrintFalse(identifier);
}

bool UnitTest::PrintTrue(std::string identifier)
{
	std::cout << white << identifier << ": " << green << "true" << white << std::endl;
	return true;
}

bool UnitTest::PrintFalse(std::string identifier)
{
	std::cout << white << identifier << ": " << red << "false" << white << std::endl;
	return false;
}


