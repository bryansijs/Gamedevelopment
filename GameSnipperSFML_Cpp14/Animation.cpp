#include "stdafx.h"
#include "Animation.h"
#include "Time.h"

Animation::Animation(GameObject* gameObject, float delay, int firstState)
{
	this->gameObject = gameObject;
	this->delay = delay;
	this->firstState = firstState;
}

Animation::~Animation()
{
}

void Animation::Animate()
{
	if (currentDelay > 0)
	{
		currentDelay = currentDelay - Time::deltaTime;
		return;
	}

	if (currentState == gameObject->GetAnimationStates())
		currentState = 0;

	gameObject->setImageX(currentState);
	currentState++;
	currentDelay = delay;
}

void Animation::Reset()
{
	currentState = firstState;
	gameObject->setImageX(currentState);
}