#pragma once
#include <iostream>

class MoveBehaviour;
class GameObject;

class MoveBehaviourFactory
{
public:
	MoveBehaviourFactory();
	~MoveBehaviourFactory();
	MoveBehaviour* Create(GameObject* gameObject);
};

