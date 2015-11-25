#include "stdafx.h"
#include "MenuContext.h"

#include "Context.h"
#include "LevelManager.h"

MenuContext::MenuContext(Context* context)
{
	this->context = context;
	this->levelManager = new LevelManager();
}

MenuContext::~MenuContext()
{
	
}