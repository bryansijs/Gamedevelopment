#include "stdafx.h"
#include "GameActions.h"
#include <vector>
#include "KeyMapping.h"
#include "GameState.h"

GameActions::GameActions(GameState* gamestate)
{
	GameActions::gamestate = gamestate;
}


GameActions::~GameActions()
{
}

void GameActions::ProcessActions()
{
	map<string, void(GameActions::*)()>::iterator it;
	for (vector<int>::size_type i = 0; i != activeKeys.size(); i++) {

		string map = KeyMapping::GetMap(activeKeys[i]);

		for (it = actions.begin(); it != actions.end(); ++it)
		{
			if (map.find(it->first) != string::npos)
			{
				if (find(activeActions.begin(), activeActions.end(), it->second) == activeActions.end())
				{
					activeActions.push_back(it->second);
				}
			}
		}
	}
	ExecuteActions();
}

void GameActions::ExecuteActions()
{
	vector<void(GameActions::*)()>::iterator it;
	for (it = activeActions.begin(); it != activeActions.end(); ++it)
	{
		auto function = *it;
		(this->*function)();
	}
	activeActions.clear();
}

void GameActions::NextLevel()
{
	gamestate->StartNextLevel();
}