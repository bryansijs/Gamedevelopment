#pragma once
#include "application.h"
#include "view.h"
#include <iostream>
#include <Awesomium/STLHelpers.h>
#include "BaseState.h"

namespace Awesomium{
	class WebView;
	class JSArray;
}

class Context;
class MenuState : public BaseState
{
	Context* context;
public:
	void run();
	MenuState(Context* context);
	~MenuState();

	void MenuState::OnSayHello(Awesomium::WebView* caller, const Awesomium::JSArray& args)
	{
		std::cout << "clicked!" << std::endl;
	}
};

