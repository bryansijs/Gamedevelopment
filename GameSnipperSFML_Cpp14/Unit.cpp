#include <vector>
#include "stdafx.h"
#include "Unit.h"
#include "MoveBehaviour.h"
#include "DrawBehaviour.h"
#include "UnitState.h"

void Unit::setCurrentState(UnitState* newState)
{
	//Verwijder uit lijst. 
	this->currentState = newState;
}

void Unit::setMoveBehaviour(MoveBehaviour* newMoveBehaviour)
{
	//Verwijder uit lijst.
	//this->setMoveBehaviour = newMoveBehaviour;
}

void Unit::setDrawBehaviour(DrawBehaviour* newDrawBehaviour)
{
	//Verwijder uit lijst. 
	this->drawBehaviour = newDrawBehaviour;
}
