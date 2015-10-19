#include "stdafx.h"
#include "NormalMoveBehaviour.h"

NormalMoveBehaviour::NormalMoveBehaviour(Unit* u)
{
	this->unit = u;
}

NormalMoveBehaviour::~NormalMoveBehaviour()
{
	//Moet ik pointers en float en int ook verwijderen ook destorying die zich zelf. 
}

void NormalMoveBehaviour::Move(float DOWN, float UP, float RIGHT, float LEFT, float deltaTime) //in pixelsaSecond (DOWN, UP, RIGHT, LEFT)
{
	if (this->checkVisible(0.0f, 0.0f)) {
		float moveDOWN = DOWN * deltaTime;
		this->unit->positions.y += moveDOWN;

		float moveUP = UP * deltaTime;
		this->unit->positions.y -= moveUP;

		float moveRIGHT = RIGHT * deltaTime;
		this->unit->positions.x += moveRIGHT;

		float moveLEFT = LEFT * deltaTime;
		this->unit->positions.x -= moveLEFT;
	}
}

bool NormalMoveBehaviour::checkVisible(int screenX, int screenY)
{
	//Wat moet ik doen wanneer ze niet meer visible zijn ook echt verwijderen ????
	//Ik heb de kamer width en height nodig. 
	return true;
}
