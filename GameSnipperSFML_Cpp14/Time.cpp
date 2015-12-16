#include "stdafx.h"
#include "Time.h"
#include <math.h>
Time::Time()
{
	delay = 0;
}

Time::~Time()
{
}

float Time::deltaTime;
float Time::runningTime;
float Time::delay;
float Time::fps;
int Time::GetFPs()
{
	if (delay < 0) {
		fps = round(1.0 / deltaTime);
		delay = 0.5f;
	}
	else
		delay -= deltaTime;
	return fps;
}