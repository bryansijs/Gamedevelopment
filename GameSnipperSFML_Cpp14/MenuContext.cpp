#include "stdafx.h"
#include "MenuContext.h"

#include "Context.h"
#include "LevelManager.h"

MenuContext::MenuContext(Context* context)
{
	this->context = context;
}

MenuContext::~MenuContext()
{
	delete music;
	delete pixels;

	delete surface;
}