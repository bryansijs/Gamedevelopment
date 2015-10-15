#include "stdafx.h"
#include "Menu.h"




Menu::~Menu()
{
	if (view_)
		app_->DestroyView(view_);
	if (app_)
		delete app_;

}

void Menu::Run()
{
	app_->Run();
}

void Menu::OnLoaded()
{
	view_ = View::Create(500, 300);
	// < Set up your View here. >

}