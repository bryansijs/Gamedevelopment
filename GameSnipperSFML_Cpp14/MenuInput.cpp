#include "stdafx.h"
#include "GameContext.h"
#include "MenuInput.h"
#include "MenuActions.h"

void MenuInput::ProcessKeyActions(MenuActions* menuActions)
{
	for (int i = 0; i < activeKeys.size(); i++)
	{
		std::string key = activeKeys[i];

		if (key == "Up")
			menuActions->NavigateUp();

		if (key == "Down")
			menuActions->NavigateDown();

		if (key == "Esc")
			menuActions->BackToMenu();

		if (key == "Return")
			menuActions->NavigateComfirm();
	}
}