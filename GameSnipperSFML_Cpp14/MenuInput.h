#pragma once
#include "BaseInput.h"

class MenuActions;

class MenuInput : public BaseInput
{
public:
	void ProcessKeyActions(MenuActions* menuActions);
};