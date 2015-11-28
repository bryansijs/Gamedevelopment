#pragma once
#include "BaseInput.h"

class MenuContext;

class MenuInput : public BaseInput
{
public:
	MenuInput(MenuContext* mContext);
	void ProcessKeyActions() override;
private:
	MenuContext* mContext;
};