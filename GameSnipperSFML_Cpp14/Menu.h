#pragma once
#include "application.h"
#include "view.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#ifdef _WIN32
#include <Windows.h>
#endif


class Menu : public Application::Listener {

	Application* app_;
	View* view_;
public:
	Menu(): app_(Application::Create()),view_(0) {
		app_->set_listener(this);
	}
	void Run();
	virtual void OnLoaded();
	~Menu();
};



