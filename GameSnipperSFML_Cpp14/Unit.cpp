#include <vector>
#include "stdafx.h"
#include "Unit.h"
#include "MoveBehaviour.h"
#include "DrawBehaviour.h"
#include "UnitState.h"


Unit::Unit():GameObject()
{

}

Unit::Unit(DrawContainer* container, std::string img) : GameObject{ container, img }
{

}

Unit::Unit(DrawContainer* dContainer, std::string img, MoveContainer* mContainer) : GameObject{ dContainer, img }
{
	//Wat voor behavoir heeft deze dan als basic?
	//this->SetMoveBehaviour()
}

Unit::Unit(DrawContainer* dContainer, std::string img, MoveContainer* mContainer, GameObjectContainer* goContainer) : GameObject{ dContainer,goContainer, mContainer, img }
{
	//Wat voor behavoir heeft deze dan als basic?
	//this->SetMoveBehaviour()
}


Unit::Unit(DrawContainer* dContainer, std::string img, GameObjectContainer* goContainer) : GameObject{ dContainer,goContainer, img, }
{
	//Wat voor behavoir heeft deze dan als basic?
	//this->SetMoveBehaviour()
}


Unit::Unit(DrawContainer* container) : GameObject{ container}
{

}
void Unit::setCurrentState(UnitState* newState)
{
	//Verwijder uit lijst. 
	this->currentState = newState;
}
