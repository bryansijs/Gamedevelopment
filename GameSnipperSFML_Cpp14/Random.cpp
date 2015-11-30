#include "stdafx.h"
#include "Random.h"

#include <iostream>
#include <random>

Random::Random()
{
}

Random::~Random()
{
}

int Random::Number(int min, int max)
{
	std::random_device dev;
	std::default_random_engine dre{ dev() };
	std::uniform_int_distribution<int> dist{ min, max };

	return dist(dre);
}