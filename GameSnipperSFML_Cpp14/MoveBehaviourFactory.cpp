#include "stdafx.h"
#include "MoveBehaviourFactory.h"
#include "NormalMoveBehaviour.h"
#include "GameObject.h"

MoveBehaviourFactory::MoveBehaviourFactory()
{
}

MoveBehaviourFactory::~MoveBehaviourFactory()
{
}

MoveBehaviour* MoveBehaviourFactory::Create(GameObject* gameObject)
{
	return new NormalMoveBehaviour(gameObject);
}

