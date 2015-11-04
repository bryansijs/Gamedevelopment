#include "stdafx.h"
#include "NormalMoveBehaviour.h"

NormalMoveBehaviour::NormalMoveBehaviour(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

NormalMoveBehaviour::~NormalMoveBehaviour()
{
	//Moet ik pointers en float en int ook verwijderen ook destorying die zich zelf. 
}

void NormalMoveBehaviour::Update()
{

}

bool NormalMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}
