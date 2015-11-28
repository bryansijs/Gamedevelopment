#include "stdafx.h"
#include "GameContext.h"
#include "MenuInput.h"
#include "MenuContext.h"
#include "MenuState.h"

MenuInput::MenuInput(MenuContext* mContext)
{
	MenuInput::mContext = mContext;
}

void MenuInput::ProcessKeyActions()
{
	for (int i = 0; i < activeKeys.size(); i++)
	{
		std::string key = activeKeys[i];

		if (key == "Up")
		{
			if (mContext->currentLevel > 1)
			{
				mContext->currentLevel -= 1;
				MenuState::callDirectJSFunction(mContext->webView, mContext->web_core, mContext->currentLevel);
			}
		}

		if (key == "Down") {
			if (mContext->currentLevel < menuItems.size())
			{
				mContext->currentLevel += 1;
				MenuState::callDirectJSFunction(mContext->webView, mContext->web_core, mContext->currentLevel);
			}
		}

		if (key == "Esc") {
			if (!mContext->inMenu)
			{
				BackToMenu();
			}
		}

		if (key == "Return") {
			std::map <int, void(MenuState::*)()>::iterator it;
			for (it = menuItems.begin(); it != menuItems.end(); ++it)
			{
				if (it->first == mContext->currentLevel)
				{
					auto function = it->second;
					(this->*function)();
					break;
				}
			}
		}
	}
}