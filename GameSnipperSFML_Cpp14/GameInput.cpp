#include "stdafx.h"
#include "GameContext.h"
#include "KeyMapping.h"
#include "GameInput.h"

GameInput::GameInput(GameContext* gContext) : BaseInput()
{
	GameInput::gContext = gContext;
}

void GameInput::ProcessKeyActions()
{
	for (int i = 0; i < activeKeys.size(); i++)
	{
		string key = KeyMapping::GetMap(activeKeys[i]);

		/* EXAMPLES:
		if (key.find("move") != string::npos)
			gContext->player->GetActions()->Move(key);

		if (key == "shoot")
			gContext->player->GetActions()->Shoot();

		if (key == "use")
			gContext->player->GetActions()->Use();
			*/
	}
}