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
