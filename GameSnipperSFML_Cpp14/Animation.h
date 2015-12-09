#pragma once

#include "GameObject.h"

class Animation
{
public:
	Animation(GameObject* gameObject, float delay, int firstState);
	~Animation();

	void Animate();
	void Reset();
private:
	GameObject* gameObject;

	int firstState;
	int currentState;
	float delay;
	float currentDelay;
};