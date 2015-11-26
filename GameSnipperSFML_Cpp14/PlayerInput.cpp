#include "stdafx.h"
#include "PlayerInput.h"
#include "GameContext.h"
#include "KeyMapping.h"

PlayerInput::PlayerInput(GameContext* gContext) : BaseInput()
{
	PlayerInput::gContext = gContext;
}

void PlayerInput::ProcessKeyActions()
{
	for (int i = 0; i < activeKeys.size(); i++)
	{
		string key = KeyMapping::GetMap(activeKeys[i]);

		if (key.find("move") != string::npos)
			gContext->player->GetActions()->Move(key);

		if (key == "shoot")
			gContext->player->GetActions()->Shoot();

		if (key == "use")
			gContext->player->GetActions()->Use();
	}
}