#include "stdafx.h"
#include "Time.h"
#include <math.h>
Time::Time()
{
}

Time::~Time()
{
}

float Time::deltaTime;
float Time::runningTime;

int Time::GetFPs()
{
	return 	round(1.0f / deltaTime);
}