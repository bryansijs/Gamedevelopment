#include "stdafx.h"
#include "MoveBehaviourFactory.h"
#include "WanderMoveBehaviour.h"
#include "GameObject.h"

MoveBehaviourFactory::MoveBehaviourFactory()
{
}

MoveBehaviourFactory::~MoveBehaviourFactory()
{
}

MoveBehaviour* MoveBehaviourFactory::Create(GameObject* gameObject)
{
	return new WanderMoveBehaviour(gameObject);
}

