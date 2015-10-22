#pragma once
namespace Awesomium{
	class WebView;
	class JSArray;
}

class Context;
class MenuState
{
	Context* context;
public:
	void run();
	MenuState(Context* context);
	~MenuState();
};

